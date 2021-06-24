<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010-2017 Intel Corporation. All Rights Reserved.
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
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_qos.h>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/iosf_mbi.h>

#समावेश "../../include/linux/atomisp_gmin_platform.h"

#समावेश "atomisp_cmd.h"
#समावेश "atomisp_common.h"
#समावेश "atomisp_fops.h"
#समावेश "atomisp_file.h"
#समावेश "atomisp_ioctl.h"
#समावेश "atomisp_internal.h"
#समावेश "atomisp_acc.h"
#समावेश "atomisp-regs.h"
#समावेश "atomisp_dfs_tables.h"
#समावेश "atomisp_drvfs.h"
#समावेश "hmm/hmm.h"
#समावेश "atomisp_trace_event.h"

#समावेश "sh_css_firmware.h"

#समावेश "device_access.h"

/* Timeouts to रुको क्रम all subdevs to be रेजिस्टरed */
#घोषणा SUBDEV_WAIT_TIMEOUT		50 /* ms */
#घोषणा SUBDEV_WAIT_TIMEOUT_MAX_COUNT	40 /* up to 2 seconds */

/* G-Min addition: pull this in from पूर्णांकel_mid_pm.h */
#घोषणा CSTATE_EXIT_LATENCY_C1  1

अटल uपूर्णांक skip_fwload;
module_param(skip_fwload, uपूर्णांक, 0644);
MODULE_PARM_DESC(skip_fwload, "Skip atomisp firmware load");

/* set reserved memory pool size in page */
अटल अचिन्हित पूर्णांक repool_pgnr = 32768;
module_param(repool_pgnr, uपूर्णांक, 0644);
MODULE_PARM_DESC(repool_pgnr,
		 "Set the reserved memory pool size in page (default:32768)");

/* set dynamic memory pool size in page */
अचिन्हित पूर्णांक dypool_pgnr = अच_पूर्णांक_उच्च;
module_param(dypool_pgnr, uपूर्णांक, 0644);
MODULE_PARM_DESC(dypool_pgnr,
		 "Set the dynamic memory pool size in page (default: unlimited)");

bool dypool_enable = true;
module_param(dypool_enable, bool, 0644);
MODULE_PARM_DESC(dypool_enable,
		 "dynamic memory pool enable/disable (default:enabled)");

/* memory optimization: deferred firmware loading */
bool defer_fw_load;
module_param(defer_fw_load, bool, 0644);
MODULE_PARM_DESC(defer_fw_load,
		 "Defer FW loading until device is opened (default:disable)");

/* cross componnet debug message flag */
पूर्णांक dbg_level;
module_param(dbg_level, पूर्णांक, 0644);
MODULE_PARM_DESC(dbg_level, "debug message level (default:0)");

/* log function चयन */
पूर्णांक dbg_func = 2;
module_param(dbg_func, पूर्णांक, 0644);
MODULE_PARM_DESC(dbg_func,
		 "log function switch non/trace_printk/printk (default:printk)");

पूर्णांक mipicsi_flag;
module_param(mipicsi_flag, पूर्णांक, 0644);
MODULE_PARM_DESC(mipicsi_flag, "mipi csi compression predictor algorithm");

अटल अक्षर firmware_name[256];
module_param_string(firmware_name, firmware_name, माप(firmware_name), 0);
MODULE_PARM_DESC(firmware_name, "Firmware file name. Allows overriding the default firmware name.");

/*set to 16x16 since this is the amount of lines and pixels the sensor
exports extra. If these are kept at the 10x8 that they were on, in yuv
करोwnscaling modes incorrect resolutions where requested to the sensor
driver with strange outcomes as a result. The proper way tot करो this
would be to have a list of tables the specअगरy the sensor res, mipi rec,
output res, and isp output res. however since we करो not have this yet,
the chosen solution is the next best thing. */
पूर्णांक pad_w = 16;
module_param(pad_w, पूर्णांक, 0644);
MODULE_PARM_DESC(pad_w, "extra data for ISP processing");

पूर्णांक pad_h = 16;
module_param(pad_h, पूर्णांक, 0644);
MODULE_PARM_DESC(pad_h, "extra data for ISP processing");

/*
 * FIXME: this is a hack to make easier to support ISP2401 variant.
 * As a given प्रणाली will either be ISP2401 or not, we can just use
 * a boolean, in order to replace existing #अगर_घोषित ISP2401 everywhere.
 *
 * Once this driver माला_लो पूर्णांकo a better shape, however, the best would
 * be to replace this to something stored inside atomisp allocated
 * काष्ठाures.
 */

काष्ठा device *atomisp_dev;

अटल स्थिर काष्ठा atomisp_freq_scaling_rule dfs_rules_merr[] = अणु
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_VIDEO,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_STILL_CAPTURE,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_CONTINUOUS_CAPTURE,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_PREVIEW,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_457MHZ,
		.run_mode = ATOMISP_RUN_MODE_SDV,
	पूर्ण,
पूर्ण;

/* Merrअगरield and Moorefield DFS rules */
अटल स्थिर काष्ठा atomisp_dfs_config dfs_config_merr = अणु
	.lowest_freq = ISP_FREQ_200MHZ,
	.max_freq_at_vmin = ISP_FREQ_400MHZ,
	.highest_freq = ISP_FREQ_457MHZ,
	.dfs_table = dfs_rules_merr,
	.dfs_table_size = ARRAY_SIZE(dfs_rules_merr),
पूर्ण;

अटल स्थिर काष्ठा atomisp_freq_scaling_rule dfs_rules_merr_1179[] = अणु
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_VIDEO,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_STILL_CAPTURE,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_CONTINUOUS_CAPTURE,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_PREVIEW,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_SDV,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा atomisp_dfs_config dfs_config_merr_1179 = अणु
	.lowest_freq = ISP_FREQ_200MHZ,
	.max_freq_at_vmin = ISP_FREQ_400MHZ,
	.highest_freq = ISP_FREQ_400MHZ,
	.dfs_table = dfs_rules_merr_1179,
	.dfs_table_size = ARRAY_SIZE(dfs_rules_merr_1179),
पूर्ण;

अटल स्थिर काष्ठा atomisp_freq_scaling_rule dfs_rules_merr_117a[] = अणु
	अणु
		.width = 1920,
		.height = 1080,
		.fps = 30,
		.isp_freq = ISP_FREQ_266MHZ,
		.run_mode = ATOMISP_RUN_MODE_VIDEO,
	पूर्ण,
	अणु
		.width = 1080,
		.height = 1920,
		.fps = 30,
		.isp_freq = ISP_FREQ_266MHZ,
		.run_mode = ATOMISP_RUN_MODE_VIDEO,
	पूर्ण,
	अणु
		.width = 1920,
		.height = 1080,
		.fps = 45,
		.isp_freq = ISP_FREQ_320MHZ,
		.run_mode = ATOMISP_RUN_MODE_VIDEO,
	पूर्ण,
	अणु
		.width = 1080,
		.height = 1920,
		.fps = 45,
		.isp_freq = ISP_FREQ_320MHZ,
		.run_mode = ATOMISP_RUN_MODE_VIDEO,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = 60,
		.isp_freq = ISP_FREQ_356MHZ,
		.run_mode = ATOMISP_RUN_MODE_VIDEO,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_200MHZ,
		.run_mode = ATOMISP_RUN_MODE_VIDEO,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_STILL_CAPTURE,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_CONTINUOUS_CAPTURE,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_200MHZ,
		.run_mode = ATOMISP_RUN_MODE_PREVIEW,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_SDV,
	पूर्ण,
पूर्ण;

अटल काष्ठा atomisp_dfs_config dfs_config_merr_117a = अणु
	.lowest_freq = ISP_FREQ_200MHZ,
	.max_freq_at_vmin = ISP_FREQ_200MHZ,
	.highest_freq = ISP_FREQ_400MHZ,
	.dfs_table = dfs_rules_merr_117a,
	.dfs_table_size = ARRAY_SIZE(dfs_rules_merr_117a),
पूर्ण;

अटल स्थिर काष्ठा atomisp_freq_scaling_rule dfs_rules_byt[] = अणु
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_VIDEO,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_STILL_CAPTURE,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_CONTINUOUS_CAPTURE,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_PREVIEW,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_400MHZ,
		.run_mode = ATOMISP_RUN_MODE_SDV,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा atomisp_dfs_config dfs_config_byt = अणु
	.lowest_freq = ISP_FREQ_200MHZ,
	.max_freq_at_vmin = ISP_FREQ_400MHZ,
	.highest_freq = ISP_FREQ_400MHZ,
	.dfs_table = dfs_rules_byt,
	.dfs_table_size = ARRAY_SIZE(dfs_rules_byt),
पूर्ण;

अटल स्थिर काष्ठा atomisp_freq_scaling_rule dfs_rules_cht[] = अणु
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_320MHZ,
		.run_mode = ATOMISP_RUN_MODE_VIDEO,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_356MHZ,
		.run_mode = ATOMISP_RUN_MODE_STILL_CAPTURE,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_320MHZ,
		.run_mode = ATOMISP_RUN_MODE_CONTINUOUS_CAPTURE,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_320MHZ,
		.run_mode = ATOMISP_RUN_MODE_PREVIEW,
	पूर्ण,
	अणु
		.width = 1280,
		.height = 720,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_320MHZ,
		.run_mode = ATOMISP_RUN_MODE_SDV,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_356MHZ,
		.run_mode = ATOMISP_RUN_MODE_SDV,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा atomisp_freq_scaling_rule dfs_rules_cht_soc[] = अणु
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_356MHZ,
		.run_mode = ATOMISP_RUN_MODE_VIDEO,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_356MHZ,
		.run_mode = ATOMISP_RUN_MODE_STILL_CAPTURE,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_320MHZ,
		.run_mode = ATOMISP_RUN_MODE_CONTINUOUS_CAPTURE,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_320MHZ,
		.run_mode = ATOMISP_RUN_MODE_PREVIEW,
	पूर्ण,
	अणु
		.width = ISP_FREQ_RULE_ANY,
		.height = ISP_FREQ_RULE_ANY,
		.fps = ISP_FREQ_RULE_ANY,
		.isp_freq = ISP_FREQ_356MHZ,
		.run_mode = ATOMISP_RUN_MODE_SDV,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा atomisp_dfs_config dfs_config_cht = अणु
	.lowest_freq = ISP_FREQ_100MHZ,
	.max_freq_at_vmin = ISP_FREQ_356MHZ,
	.highest_freq = ISP_FREQ_356MHZ,
	.dfs_table = dfs_rules_cht,
	.dfs_table_size = ARRAY_SIZE(dfs_rules_cht),
पूर्ण;

/* This one should be visible also by atomisp_cmd.c */
स्थिर काष्ठा atomisp_dfs_config dfs_config_cht_soc = अणु
	.lowest_freq = ISP_FREQ_100MHZ,
	.max_freq_at_vmin = ISP_FREQ_356MHZ,
	.highest_freq = ISP_FREQ_356MHZ,
	.dfs_table = dfs_rules_cht_soc,
	.dfs_table_size = ARRAY_SIZE(dfs_rules_cht_soc),
पूर्ण;

पूर्णांक atomisp_video_init(काष्ठा atomisp_video_pipe *video, स्थिर अक्षर *name)
अणु
	पूर्णांक ret;
	स्थिर अक्षर *direction;

	चयन (video->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		direction = "output";
		video->pad.flags = MEDIA_PAD_FL_SINK;
		video->vdev.fops = &atomisp_fops;
		video->vdev.ioctl_ops = &atomisp_ioctl_ops;
		अवरोध;
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		direction = "input";
		video->pad.flags = MEDIA_PAD_FL_SOURCE;
		video->vdev.fops = &atomisp_file_fops;
		video->vdev.ioctl_ops = &atomisp_file_ioctl_ops;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = media_entity_pads_init(&video->vdev.entity, 1, &video->pad);
	अगर (ret < 0)
		वापस ret;

	/* Initialize the video device. */
	snम_लिखो(video->vdev.name, माप(video->vdev.name),
		 "ATOMISP ISP %s %s", name, direction);
	video->vdev.release = video_device_release_empty;
	video_set_drvdata(&video->vdev, video->isp);

	वापस 0;
पूर्ण

व्योम atomisp_acc_init(काष्ठा atomisp_acc_pipe *video, स्थिर अक्षर *name)
अणु
	video->vdev.fops = &atomisp_fops;
	video->vdev.ioctl_ops = &atomisp_ioctl_ops;

	/* Initialize the video device. */
	snम_लिखो(video->vdev.name, माप(video->vdev.name),
		 "ATOMISP ISP %s", name);
	video->vdev.release = video_device_release_empty;
	video_set_drvdata(&video->vdev, video->isp);
पूर्ण

व्योम atomisp_video_unरेजिस्टर(काष्ठा atomisp_video_pipe *video)
अणु
	अगर (video_is_रेजिस्टरed(&video->vdev)) अणु
		media_entity_cleanup(&video->vdev.entity);
		video_unरेजिस्टर_device(&video->vdev);
	पूर्ण
पूर्ण

व्योम atomisp_acc_unरेजिस्टर(काष्ठा atomisp_acc_pipe *video)
अणु
	अगर (video_is_रेजिस्टरed(&video->vdev))
		video_unरेजिस्टर_device(&video->vdev);
पूर्ण

अटल पूर्णांक atomisp_save_iunit_reg(काष्ठा atomisp_device *isp)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(isp->dev);

	dev_dbg(isp->dev, "%s\n", __func__);

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &isp->saved_regs.pcicmdsts);
	/* isp->saved_regs.ispmmadr is set from the atomisp_pci_probe() */
	pci_पढ़ो_config_dword(pdev, PCI_MSI_CAPID, &isp->saved_regs.msicap);
	pci_पढ़ो_config_dword(pdev, PCI_MSI_ADDR, &isp->saved_regs.msi_addr);
	pci_पढ़ो_config_word(pdev, PCI_MSI_DATA,  &isp->saved_regs.msi_data);
	pci_पढ़ो_config_byte(pdev, PCI_INTERRUPT_LINE, &isp->saved_regs.पूर्णांकr);
	pci_पढ़ो_config_dword(pdev, PCI_INTERRUPT_CTRL, &isp->saved_regs.पूर्णांकerrupt_control);

	pci_पढ़ो_config_dword(pdev, MRFLD_PCI_PMCS, &isp->saved_regs.pmcs);
	/* Ensure पढ़ो/ग_लिखो combining is enabled. */
	pci_पढ़ो_config_dword(pdev, PCI_I_CONTROL, &isp->saved_regs.i_control);
	isp->saved_regs.i_control |=
	    MRFLD_PCI_I_CONTROL_ENABLE_READ_COMBINING |
	    MRFLD_PCI_I_CONTROL_ENABLE_WRITE_COMBINING;
	pci_पढ़ो_config_dword(pdev, MRFLD_PCI_CSI_ACCESS_CTRL_VIOL,
			      &isp->saved_regs.csi_access_viol);
	pci_पढ़ो_config_dword(pdev, MRFLD_PCI_CSI_RCOMP_CONTROL,
			      &isp->saved_regs.csi_rcomp_config);
	/*
	 * Hardware bugs require setting CSI_HS_OVR_CLK_GATE_ON_UPDATE.
	 * ANN/CHV: RCOMP updates करो not happen when using CSI2+ path
	 * and sensor sending "continuous clock".
	 * TNG/ANN/CHV: MIPI packets are lost अगर the HS entry sequence
	 * is missed, and IUNIT can hang.
	 * For both issues, setting this bit is a workaround.
	 */
	isp->saved_regs.csi_rcomp_config |= MRFLD_PCI_CSI_HS_OVR_CLK_GATE_ON_UPDATE;
	pci_पढ़ो_config_dword(pdev, MRFLD_PCI_CSI_AFE_TRIM_CONTROL,
			      &isp->saved_regs.csi_afe_dly);
	pci_पढ़ो_config_dword(pdev, MRFLD_PCI_CSI_CONTROL,
			      &isp->saved_regs.csi_control);
	अगर (isp->media_dev.hw_revision >=
	    (ATOMISP_HW_REVISION_ISP2401 << ATOMISP_HW_REVISION_SHIFT))
		isp->saved_regs.csi_control |= MRFLD_PCI_CSI_CONTROL_PARPATHEN;
	/*
	 * On CHT CSI_READY bit should be enabled beक्रमe stream on
	 */
	अगर (IS_CHT && (isp->media_dev.hw_revision >= ((ATOMISP_HW_REVISION_ISP2401 <<
		       ATOMISP_HW_REVISION_SHIFT) | ATOMISP_HW_STEPPING_B0)))
		isp->saved_regs.csi_control |= MRFLD_PCI_CSI_CONTROL_CSI_READY;
	pci_पढ़ो_config_dword(pdev, MRFLD_PCI_CSI_AFE_RCOMP_CONTROL,
			      &isp->saved_regs.csi_afe_rcomp_config);
	pci_पढ़ो_config_dword(pdev, MRFLD_PCI_CSI_AFE_HS_CONTROL,
			      &isp->saved_regs.csi_afe_hs_control);
	pci_पढ़ो_config_dword(pdev, MRFLD_PCI_CSI_DEADLINE_CONTROL,
			      &isp->saved_regs.csi_deadline_control);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused atomisp_restore_iunit_reg(काष्ठा atomisp_device *isp)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(isp->dev);

	dev_dbg(isp->dev, "%s\n", __func__);

	pci_ग_लिखो_config_word(pdev, PCI_COMMAND, isp->saved_regs.pcicmdsts);
	pci_ग_लिखो_config_dword(pdev, PCI_BASE_ADDRESS_0, isp->saved_regs.ispmmadr);
	pci_ग_लिखो_config_dword(pdev, PCI_MSI_CAPID, isp->saved_regs.msicap);
	pci_ग_लिखो_config_dword(pdev, PCI_MSI_ADDR, isp->saved_regs.msi_addr);
	pci_ग_लिखो_config_word(pdev, PCI_MSI_DATA, isp->saved_regs.msi_data);
	pci_ग_लिखो_config_byte(pdev, PCI_INTERRUPT_LINE, isp->saved_regs.पूर्णांकr);
	pci_ग_लिखो_config_dword(pdev, PCI_INTERRUPT_CTRL, isp->saved_regs.पूर्णांकerrupt_control);
	pci_ग_लिखो_config_dword(pdev, PCI_I_CONTROL, isp->saved_regs.i_control);

	pci_ग_लिखो_config_dword(pdev, MRFLD_PCI_PMCS, isp->saved_regs.pmcs);
	pci_ग_लिखो_config_dword(pdev, MRFLD_PCI_CSI_ACCESS_CTRL_VIOL,
			       isp->saved_regs.csi_access_viol);
	pci_ग_लिखो_config_dword(pdev, MRFLD_PCI_CSI_RCOMP_CONTROL,
			       isp->saved_regs.csi_rcomp_config);
	pci_ग_लिखो_config_dword(pdev, MRFLD_PCI_CSI_AFE_TRIM_CONTROL,
			       isp->saved_regs.csi_afe_dly);
	pci_ग_लिखो_config_dword(pdev, MRFLD_PCI_CSI_CONTROL,
			       isp->saved_regs.csi_control);
	pci_ग_लिखो_config_dword(pdev, MRFLD_PCI_CSI_AFE_RCOMP_CONTROL,
			       isp->saved_regs.csi_afe_rcomp_config);
	pci_ग_लिखो_config_dword(pdev, MRFLD_PCI_CSI_AFE_HS_CONTROL,
			       isp->saved_regs.csi_afe_hs_control);
	pci_ग_लिखो_config_dword(pdev, MRFLD_PCI_CSI_DEADLINE_CONTROL,
			       isp->saved_regs.csi_deadline_control);

	/*
	 * क्रम MRFLD, Software/firmware needs to ग_लिखो a 1 to bit0
	 * of the रेजिस्टर at CSI_RECEIVER_SELECTION_REG to enable
	 * SH CSI backend ग_लिखो 0 will enable Arasan CSI backend,
	 * which has bugs(like sighting:4567697 and 4567699) and
	 * will be हटाओd in B0
	 */
	atomisp_css2_hw_store_32(MRFLD_CSI_RECEIVER_SELECTION_REG, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक atomisp_mrfld_pre_घातer_करोwn(काष्ठा atomisp_device *isp)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(isp->dev);
	u32 irq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&isp->lock, flags);
	अगर (isp->sw_contex.घातer_state == ATOM_ISP_POWER_DOWN) अणु
		spin_unlock_irqrestore(&isp->lock, flags);
		dev_dbg(isp->dev, "<%s %d.\n", __func__, __LINE__);
		वापस 0;
	पूर्ण
	/*
	 * MRFLD HAS requirement: cannot घातer off i-unit अगर
	 * ISP has IRQ not serviced.
	 * So, here we need to check अगर there is any pending
	 * IRQ, अगर so, रुकोing क्रम it to be served
	 */
	pci_पढ़ो_config_dword(pdev, PCI_INTERRUPT_CTRL, &irq);
	irq = irq & 1 << INTR_IIR;
	pci_ग_लिखो_config_dword(pdev, PCI_INTERRUPT_CTRL, irq);

	pci_पढ़ो_config_dword(pdev, PCI_INTERRUPT_CTRL, &irq);
	अगर (!(irq & (1 << INTR_IIR)))
		जाओ करोne;

	atomisp_css2_hw_store_32(MRFLD_INTR_CLEAR_REG, 0xFFFFFFFF);
	atomisp_load_uपूर्णांक32(MRFLD_INTR_STATUS_REG, &irq);
	अगर (irq != 0) अणु
		dev_err(isp->dev,
			"%s: fail to clear isp interrupt status reg=0x%x\n",
			__func__, irq);
		spin_unlock_irqrestore(&isp->lock, flags);
		वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_dword(pdev, PCI_INTERRUPT_CTRL, &irq);
		irq = irq & 1 << INTR_IIR;
		pci_ग_लिखो_config_dword(pdev, PCI_INTERRUPT_CTRL, irq);

		pci_पढ़ो_config_dword(pdev, PCI_INTERRUPT_CTRL, &irq);
		अगर (!(irq & (1 << INTR_IIR))) अणु
			atomisp_css2_hw_store_32(MRFLD_INTR_ENABLE_REG, 0x0);
			जाओ करोne;
		पूर्ण
		dev_err(isp->dev,
			"%s: error in iunit interrupt. status reg=0x%x\n",
			__func__, irq);
		spin_unlock_irqrestore(&isp->lock, flags);
		वापस -EAGAIN;
	पूर्ण
करोne:
	/*
	* MRFLD WORKAROUND:
	* beक्रमe घातering off IUNIT, clear the pending पूर्णांकerrupts
	* and disable the पूर्णांकerrupt. driver should aव्योम writing 0
	* to IIR. It could block subsequent पूर्णांकerrupt messages.
	* HW sighting:4568410.
	*/
	pci_पढ़ो_config_dword(pdev, PCI_INTERRUPT_CTRL, &irq);
	irq &= ~(1 << INTR_IER);
	pci_ग_लिखो_config_dword(pdev, PCI_INTERRUPT_CTRL, irq);

	atomisp_msi_irq_uninit(isp);
	atomisp_freq_scaling(isp, ATOMISP_DFS_MODE_LOW, true);
	spin_unlock_irqrestore(&isp->lock, flags);

	वापस 0;
पूर्ण

/*
* WA क्रम DDR DVFS enable/disable
* By शेष, ISP will क्रमce DDR DVFS 1600MHz beक्रमe disable DVFS
*/
अटल व्योम punit_ddr_dvfs_enable(bool enable)
अणु
	पूर्णांक करोor_bell = 1 << 8;
	पूर्णांक max_रुको = 30;
	पूर्णांक reg;

	iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ, MRFLD_ISPSSDVFS, &reg);
	अगर (enable) अणु
		reg &= ~(MRFLD_BIT0 | MRFLD_BIT1);
	पूर्ण अन्यथा अणु
		reg |= (MRFLD_BIT1 | करोor_bell);
		reg &= ~(MRFLD_BIT0);
	पूर्ण
	iosf_mbi_ग_लिखो(BT_MBI_UNIT_PMC, MBI_REG_WRITE, MRFLD_ISPSSDVFS, reg);

	/* Check Req_ACK to see freq status, रुको until करोor_bell is cleared */
	जबतक ((reg & करोor_bell) && max_रुको--) अणु
		iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ, MRFLD_ISPSSDVFS, &reg);
		usleep_range(100, 500);
	पूर्ण

	अगर (max_रुको == -1)
		pr_info("DDR DVFS, door bell is not cleared within 3ms\n");
पूर्ण

अटल पूर्णांक atomisp_mrfld_घातer(काष्ठा atomisp_device *isp, bool enable)
अणु
	अचिन्हित दीर्घ समयout;
	u32 val = enable ? MRFLD_ISPSSPM0_IUNIT_POWER_ON :
			   MRFLD_ISPSSPM0_IUNIT_POWER_OFF;

	dev_dbg(isp->dev, "IUNIT power-%s.\n", enable ? "on" : "off");

	/*WA:Enable DVFS*/
	अगर (IS_CHT && enable)
		punit_ddr_dvfs_enable(true);

	/*
	 * FIXME:WA क्रम ECS28A, with this sleep, CTS
	 * android.hardware.camera2.cts.CameraDeviceTest#testCameraDeviceAbort
	 * PASS, no impact on other platक्रमms
	*/
	अगर (IS_BYT && enable)
		msleep(10);

	/* Write to ISPSSPM0 bit[1:0] to घातer on/off the IUNIT */
	iosf_mbi_modअगरy(BT_MBI_UNIT_PMC, MBI_REG_READ, MRFLD_ISPSSPM0,
			val, MRFLD_ISPSSPM0_ISPSSC_MASK);

	/*WA:Enable DVFS*/
	अगर (IS_CHT && !enable)
		punit_ddr_dvfs_enable(true);

	/*
	 * There should be no IUNIT access जबतक घातer-करोwn is
	 * in progress. HW sighting: 4567865.
	 * Wait up to 50 ms क्रम the IUNIT to shut करोwn.
	 * And we करो the same क्रम घातer on.
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(50);
	करो अणु
		u32 पंचांगp;

		/* Wait until ISPSSPM0 bit[25:24] shows the right value */
		iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ, MRFLD_ISPSSPM0, &पंचांगp);
		पंचांगp = (पंचांगp >> MRFLD_ISPSSPM0_ISPSSS_OFFSET) & MRFLD_ISPSSPM0_ISPSSC_MASK;
		अगर (पंचांगp == val) अणु
			trace_ipu_cstate(enable);
			वापस 0;
		पूर्ण

		अगर (समय_after(jअगरfies, समयout))
			अवरोध;

		/* FIXME: experienced value क्रम delay */
		usleep_range(100, 150);
	पूर्ण जबतक (1);

	अगर (enable)
		msleep(10);

	dev_err(isp->dev, "IUNIT power-%s timeout.\n", enable ? "on" : "off");
	वापस -EBUSY;
पूर्ण

/* Workaround क्रम pmu_nc_set_घातer_state not पढ़ोy in MRFLD */
पूर्णांक atomisp_mrfld_घातer_करोwn(काष्ठा atomisp_device *isp)
अणु
	वापस atomisp_mrfld_घातer(isp, false);
पूर्ण

/* Workaround क्रम pmu_nc_set_घातer_state not पढ़ोy in MRFLD */
पूर्णांक atomisp_mrfld_घातer_up(काष्ठा atomisp_device *isp)
अणु
	वापस atomisp_mrfld_घातer(isp, true);
पूर्ण

पूर्णांक atomisp_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा atomisp_device *isp = (काष्ठा atomisp_device *)
				     dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = atomisp_mrfld_pre_घातer_करोwn(isp);
	अगर (ret)
		वापस ret;

	/*Turn off the ISP d-phy*/
	ret = atomisp_ospm_dphy_करोwn(isp);
	अगर (ret)
		वापस ret;
	cpu_latency_qos_update_request(&isp->pm_qos, PM_QOS_DEFAULT_VALUE);
	वापस atomisp_mrfld_घातer_करोwn(isp);
पूर्ण

पूर्णांक atomisp_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा atomisp_device *isp = (काष्ठा atomisp_device *)
				     dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = atomisp_mrfld_घातer_up(isp);
	अगर (ret)
		वापस ret;

	cpu_latency_qos_update_request(&isp->pm_qos, isp->max_isr_latency);
	अगर (isp->sw_contex.घातer_state == ATOM_ISP_POWER_DOWN) अणु
		/*Turn on ISP d-phy */
		ret = atomisp_ospm_dphy_up(isp);
		अगर (ret) अणु
			dev_err(isp->dev, "Failed to power up ISP!.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*restore रेजिस्टर values क्रम iUnit and iUnitPHY रेजिस्टरs*/
	अगर (isp->saved_regs.pcicmdsts)
		atomisp_restore_iunit_reg(isp);

	atomisp_freq_scaling(isp, ATOMISP_DFS_MODE_LOW, true);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused atomisp_suspend(काष्ठा device *dev)
अणु
	काष्ठा atomisp_device *isp = (काष्ठा atomisp_device *)
				     dev_get_drvdata(dev);
	/* FIXME: only has one isp_subdev at present */
	काष्ठा atomisp_sub_device *asd = &isp->asd[0];
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/*
	 * FIXME: Suspend is not supported by sensors. Abort अगर any video
	 * node was खोलोed.
	 */
	अगर (atomisp_dev_users(isp))
		वापस -EBUSY;

	spin_lock_irqsave(&isp->lock, flags);
	अगर (asd->streaming != ATOMISP_DEVICE_STREAMING_DISABLED) अणु
		spin_unlock_irqrestore(&isp->lock, flags);
		dev_err(isp->dev, "atomisp cannot suspend at this time.\n");
		वापस -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&isp->lock, flags);

	ret = atomisp_mrfld_pre_घातer_करोwn(isp);
	अगर (ret)
		वापस ret;

	/*Turn off the ISP d-phy */
	ret = atomisp_ospm_dphy_करोwn(isp);
	अगर (ret) अणु
		dev_err(isp->dev, "fail to power off ISP\n");
		वापस ret;
	पूर्ण
	cpu_latency_qos_update_request(&isp->pm_qos, PM_QOS_DEFAULT_VALUE);
	वापस atomisp_mrfld_घातer_करोwn(isp);
पूर्ण

अटल पूर्णांक __maybe_unused atomisp_resume(काष्ठा device *dev)
अणु
	काष्ठा atomisp_device *isp = (काष्ठा atomisp_device *)
				     dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = atomisp_mrfld_घातer_up(isp);
	अगर (ret)
		वापस ret;

	cpu_latency_qos_update_request(&isp->pm_qos, isp->max_isr_latency);

	/*Turn on ISP d-phy */
	ret = atomisp_ospm_dphy_up(isp);
	अगर (ret) अणु
		dev_err(isp->dev, "Failed to power up ISP!.\n");
		वापस -EINVAL;
	पूर्ण

	/*restore रेजिस्टर values क्रम iUnit and iUnitPHY रेजिस्टरs*/
	अगर (isp->saved_regs.pcicmdsts)
		atomisp_restore_iunit_reg(isp);

	atomisp_freq_scaling(isp, ATOMISP_DFS_MODE_LOW, true);
	वापस 0;
पूर्ण

पूर्णांक atomisp_csi_lane_config(काष्ठा atomisp_device *isp)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(isp->dev);
	अटल स्थिर काष्ठा अणु
		u8 code;
		u8 lanes[MRFLD_PORT_NUM];
	पूर्ण portconfigs[] = अणु
		/* Tangier/Merrअगरield available lane configurations */
		अणु 0x00, अणु 4, 1, 0 पूर्ण पूर्ण,		/* 00000 */
		अणु 0x01, अणु 3, 1, 0 पूर्ण पूर्ण,		/* 00001 */
		अणु 0x02, अणु 2, 1, 0 पूर्ण पूर्ण,		/* 00010 */
		अणु 0x03, अणु 1, 1, 0 पूर्ण पूर्ण,		/* 00011 */
		अणु 0x04, अणु 2, 1, 2 पूर्ण पूर्ण,		/* 00100 */
		अणु 0x08, अणु 3, 1, 1 पूर्ण पूर्ण,		/* 01000 */
		अणु 0x09, अणु 2, 1, 1 पूर्ण पूर्ण,		/* 01001 */
		अणु 0x0a, अणु 1, 1, 1 पूर्ण पूर्ण,		/* 01010 */

		/* Anniedale/Moorefield only configurations */
		अणु 0x10, अणु 4, 2, 0 पूर्ण पूर्ण,		/* 10000 */
		अणु 0x11, अणु 3, 2, 0 पूर्ण पूर्ण,		/* 10001 */
		अणु 0x12, अणु 2, 2, 0 पूर्ण पूर्ण,		/* 10010 */
		अणु 0x13, अणु 1, 2, 0 पूर्ण पूर्ण,		/* 10011 */
		अणु 0x14, अणु 2, 2, 2 पूर्ण पूर्ण,		/* 10100 */
		अणु 0x18, अणु 3, 2, 1 पूर्ण पूर्ण,		/* 11000 */
		अणु 0x19, अणु 2, 2, 1 पूर्ण पूर्ण,		/* 11001 */
		अणु 0x1a, अणु 1, 2, 1 पूर्ण पूर्ण,		/* 11010 */
	पूर्ण;

	अचिन्हित पूर्णांक i, j;
	u8 sensor_lanes[MRFLD_PORT_NUM] = अणु 0 पूर्ण;
	u32 csi_control;
	पूर्णांक nportconfigs;
	u32 port_config_mask;
	पूर्णांक port3_lanes_shअगरt;

	अगर (isp->media_dev.hw_revision <
	    ATOMISP_HW_REVISION_ISP2401_LEGACY <<
	    ATOMISP_HW_REVISION_SHIFT) अणु
		/* Merrअगरield */
		port_config_mask = MRFLD_PORT_CONFIG_MASK;
		port3_lanes_shअगरt = MRFLD_PORT3_LANES_SHIFT;
	पूर्ण अन्यथा अणु
		/* Moorefield / Cherryview */
		port_config_mask = CHV_PORT_CONFIG_MASK;
		port3_lanes_shअगरt = CHV_PORT3_LANES_SHIFT;
	पूर्ण

	अगर (isp->media_dev.hw_revision <
	    ATOMISP_HW_REVISION_ISP2401 <<
	    ATOMISP_HW_REVISION_SHIFT) अणु
		/* Merrअगरield / Moorefield legacy input प्रणाली */
		nportconfigs = MRFLD_PORT_CONFIG_NUM;
	पूर्ण अन्यथा अणु
		/* Moorefield / Cherryview new input प्रणाली */
		nportconfigs = ARRAY_SIZE(portconfigs);
	पूर्ण

	क्रम (i = 0; i < isp->input_cnt; i++) अणु
		काष्ठा camera_mipi_info *mipi_info;

		अगर (isp->inमाला_दो[i].type != RAW_CAMERA &&
		    isp->inमाला_दो[i].type != SOC_CAMERA)
			जारी;

		mipi_info = atomisp_to_sensor_mipi_info(isp->inमाला_दो[i].camera);
		अगर (!mipi_info)
			जारी;

		चयन (mipi_info->port) अणु
		हाल ATOMISP_CAMERA_PORT_PRIMARY:
			sensor_lanes[0] = mipi_info->num_lanes;
			अवरोध;
		हाल ATOMISP_CAMERA_PORT_SECONDARY:
			sensor_lanes[1] = mipi_info->num_lanes;
			अवरोध;
		हाल ATOMISP_CAMERA_PORT_TERTIARY:
			sensor_lanes[2] = mipi_info->num_lanes;
			अवरोध;
		शेष:
			dev_err(isp->dev,
				"%s: invalid port: %d for the %dth sensor\n",
				__func__, mipi_info->port, i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nportconfigs; i++) अणु
		क्रम (j = 0; j < MRFLD_PORT_NUM; j++)
			अगर (sensor_lanes[j] &&
			    sensor_lanes[j] != portconfigs[i].lanes[j])
				अवरोध;

		अगर (j == MRFLD_PORT_NUM)
			अवरोध;			/* Found matching setting */
	पूर्ण

	अगर (i >= nportconfigs) अणु
		dev_err(isp->dev,
			"%s: could not find the CSI port setting for %d-%d-%d\n",
			__func__,
			sensor_lanes[0], sensor_lanes[1], sensor_lanes[2]);
		वापस -EINVAL;
	पूर्ण

	pci_पढ़ो_config_dword(pdev, MRFLD_PCI_CSI_CONTROL, &csi_control);
	csi_control &= ~port_config_mask;
	csi_control |= (portconfigs[i].code << MRFLD_PORT_CONFIGCODE_SHIFT)
		       | (portconfigs[i].lanes[0] ? 0 : (1 << MRFLD_PORT1_ENABLE_SHIFT))
		       | (portconfigs[i].lanes[1] ? 0 : (1 << MRFLD_PORT2_ENABLE_SHIFT))
		       | (portconfigs[i].lanes[2] ? 0 : (1 << MRFLD_PORT3_ENABLE_SHIFT))
		       | (((1 << portconfigs[i].lanes[0]) - 1) << MRFLD_PORT1_LANES_SHIFT)
		       | (((1 << portconfigs[i].lanes[1]) - 1) << MRFLD_PORT2_LANES_SHIFT)
		       | (((1 << portconfigs[i].lanes[2]) - 1) << port3_lanes_shअगरt);

	pci_ग_लिखो_config_dword(pdev, MRFLD_PCI_CSI_CONTROL, csi_control);

	dev_dbg(isp->dev,
		"%s: the portconfig is %d-%d-%d, CSI_CONTROL is 0x%08X\n",
		__func__, portconfigs[i].lanes[0], portconfigs[i].lanes[1],
		portconfigs[i].lanes[2], csi_control);

	वापस 0;
पूर्ण

अटल पूर्णांक atomisp_subdev_probe(काष्ठा atomisp_device *isp)
अणु
	स्थिर काष्ठा atomisp_platक्रमm_data *pdata;
	काष्ठा पूर्णांकel_v4l2_subdev_table *subdevs;
	पूर्णांक ret, raw_index = -1, count;

	pdata = atomisp_get_platक्रमm_data();
	अगर (!pdata) अणु
		dev_err(isp->dev, "no platform data available\n");
		वापस 0;
	पूर्ण

	/* FIXME: should वापस -EPROBE_DEFER अगर not all subdevs were probed */
	क्रम (count = 0; count < SUBDEV_WAIT_TIMEOUT_MAX_COUNT; count++) अणु
		पूर्णांक camera_count = 0;

		क्रम (subdevs = pdata->subdevs; subdevs->type; ++subdevs) अणु
			अगर (subdevs->type == RAW_CAMERA ||
			    subdevs->type == SOC_CAMERA)
				camera_count++;
		पूर्ण
		अगर (camera_count)
			अवरोध;
		msleep(SUBDEV_WAIT_TIMEOUT);
	पूर्ण
	/* Wait more समय to give more समय क्रम subdev init code to finish */
	msleep(5 * SUBDEV_WAIT_TIMEOUT);

	/* FIXME: should, instead, use I2C probe */

	क्रम (subdevs = pdata->subdevs; subdevs->type; ++subdevs) अणु
		काष्ठा v4l2_subdev *subdev;
		काष्ठा i2c_board_info *board_info =
			    &subdevs->v4l2_subdev.board_info;
		काष्ठा i2c_adapter *adapter =
		    i2c_get_adapter(subdevs->v4l2_subdev.i2c_adapter_id);
		पूर्णांक sensor_num, i;

		dev_info(isp->dev, "Probing Subdev %s\n", board_info->type);

		अगर (!adapter) अणु
			dev_err(isp->dev,
				"Failed to find i2c adapter for subdev %s\n",
				board_info->type);
			अवरोध;
		पूर्ण

		/* In G-Min, the sensor devices will alपढ़ोy be probed
		 * (via ACPI) and रेजिस्टरed, करो not create new
		 * ones */
		subdev = atomisp_gmin_find_subdev(adapter, board_info);
		अगर (!subdev) अणु
			dev_warn(isp->dev, "Subdev %s not found\n",
				 board_info->type);
			जारी;
		पूर्ण
		ret = v4l2_device_रेजिस्टर_subdev(&isp->v4l2_dev, subdev);
		अगर (ret) अणु
			dev_warn(isp->dev, "Subdev %s detection fail\n",
				 board_info->type);
			जारी;
		पूर्ण

		अगर (!subdev) अणु
			dev_warn(isp->dev, "Subdev %s detection fail\n",
				 board_info->type);
			जारी;
		पूर्ण

		dev_info(isp->dev, "Subdev %s successfully register\n",
			 board_info->type);

		चयन (subdevs->type) अणु
		हाल RAW_CAMERA:
			dev_dbg(isp->dev, "raw_index: %d\n", raw_index);
			raw_index = isp->input_cnt;
			fallthrough;
		हाल SOC_CAMERA:
			dev_dbg(isp->dev, "SOC_INDEX: %d\n", isp->input_cnt);
			अगर (isp->input_cnt >= ATOM_ISP_MAX_INPUTS) अणु
				dev_warn(isp->dev,
					 "too many atomisp inputs, ignored\n");
				अवरोध;
			पूर्ण

			isp->inमाला_दो[isp->input_cnt].type = subdevs->type;
			isp->inमाला_दो[isp->input_cnt].port = subdevs->port;
			isp->inमाला_दो[isp->input_cnt].camera = subdev;
			isp->inमाला_दो[isp->input_cnt].sensor_index = 0;
			/*
			 * initialize the subdev frame size, then next we can
			 * judge whether frame_size store effective value via
			 * pixel_क्रमmat.
			 */
			isp->inमाला_दो[isp->input_cnt].frame_size.pixel_क्रमmat = 0;
			isp->inमाला_दो[isp->input_cnt].camera_caps =
			    atomisp_get_शेष_camera_caps();
			sensor_num = isp->inमाला_दो[isp->input_cnt]
				     .camera_caps->sensor_num;
			isp->input_cnt++;
			क्रम (i = 1; i < sensor_num; i++) अणु
				अगर (isp->input_cnt >= ATOM_ISP_MAX_INPUTS) अणु
					dev_warn(isp->dev,
						 "atomisp inputs out of range\n");
					अवरोध;
				पूर्ण
				isp->inमाला_दो[isp->input_cnt] =
				    isp->inमाला_दो[isp->input_cnt - 1];
				isp->inमाला_दो[isp->input_cnt].sensor_index = i;
				isp->input_cnt++;
			पूर्ण
			अवरोध;
		हाल CAMERA_MOTOR:
			अगर (isp->motor) अणु
				dev_warn(isp->dev,
					 "too many atomisp motors, ignored %s\n",
					 board_info->type);
				जारी;
			पूर्ण
			isp->motor = subdev;
			अवरोध;
		हाल LED_FLASH:
		हाल XENON_FLASH:
			अगर (isp->flash) अणु
				dev_warn(isp->dev,
					 "too many atomisp flash devices, ignored %s\n",
					 board_info->type);
				जारी;
			पूर्ण
			isp->flash = subdev;
			अवरोध;
		शेष:
			dev_dbg(isp->dev, "unknown subdev probed\n");
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * HACK: Currently VCM beदीर्घs to primary sensor only, but correct
	 * approach must be to acquire from platक्रमm code which sensor
	 * owns it.
	 */
	अगर (isp->motor && raw_index >= 0)
		isp->inमाला_दो[raw_index].motor = isp->motor;

	/* Proceed even अगर no modules detected. For COS mode and no modules. */
	अगर (!isp->input_cnt)
		dev_warn(isp->dev, "no camera attached or fail to detect\n");
	अन्यथा
		dev_info(isp->dev, "detected %d camera sensors\n",
			 isp->input_cnt);

	वापस atomisp_csi_lane_config(isp);
पूर्ण

अटल व्योम atomisp_unरेजिस्टर_entities(काष्ठा atomisp_device *isp)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा v4l2_subdev *sd, *next;

	क्रम (i = 0; i < isp->num_of_streams; i++)
		atomisp_subdev_unरेजिस्टर_entities(&isp->asd[i]);
	atomisp_tpg_unरेजिस्टर_entities(&isp->tpg);
	atomisp_file_input_unरेजिस्टर_entities(&isp->file_dev);
	क्रम (i = 0; i < ATOMISP_CAMERA_NR_PORTS; i++)
		atomisp_mipi_csi2_unरेजिस्टर_entities(&isp->csi2_port[i]);

	list_क्रम_each_entry_safe(sd, next, &isp->v4l2_dev.subdevs, list)
	v4l2_device_unरेजिस्टर_subdev(sd);

	v4l2_device_unरेजिस्टर(&isp->v4l2_dev);
	media_device_unरेजिस्टर(&isp->media_dev);
पूर्ण

अटल पूर्णांक atomisp_रेजिस्टर_entities(काष्ठा atomisp_device *isp)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i;

	isp->media_dev.dev = isp->dev;

	strscpy(isp->media_dev.model, "Intel Atom ISP",
		माप(isp->media_dev.model));

	media_device_init(&isp->media_dev);
	isp->v4l2_dev.mdev = &isp->media_dev;
	ret = v4l2_device_रेजिस्टर(isp->dev, &isp->v4l2_dev);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "%s: V4L2 device registration failed (%d)\n",
			__func__, ret);
		जाओ v4l2_device_failed;
	पूर्ण

	ret = atomisp_subdev_probe(isp);
	अगर (ret < 0)
		जाओ csi_and_subdev_probe_failed;

	/* Register पूर्णांकernal entities */
	क्रम (i = 0; i < ATOMISP_CAMERA_NR_PORTS; i++) अणु
		ret = atomisp_mipi_csi2_रेजिस्टर_entities(&isp->csi2_port[i],
			&isp->v4l2_dev);
		अगर (ret == 0)
			जारी;

		/* error हाल */
		dev_err(isp->dev, "failed to register the CSI port: %d\n", i);
		/* deरेजिस्टर all रेजिस्टरed CSI ports */
		जबतक (i--)
			atomisp_mipi_csi2_unरेजिस्टर_entities(
			    &isp->csi2_port[i]);

		जाओ csi_and_subdev_probe_failed;
	पूर्ण

	ret =
	    atomisp_file_input_रेजिस्टर_entities(&isp->file_dev, &isp->v4l2_dev);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "atomisp_file_input_register_entities\n");
		जाओ file_input_रेजिस्टर_failed;
	पूर्ण

	ret = atomisp_tpg_रेजिस्टर_entities(&isp->tpg, &isp->v4l2_dev);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "atomisp_tpg_register_entities\n");
		जाओ tpg_रेजिस्टर_failed;
	पूर्ण

	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		काष्ठा atomisp_sub_device *asd = &isp->asd[i];

		ret = atomisp_subdev_रेजिस्टर_entities(asd, &isp->v4l2_dev);
		अगर (ret < 0) अणु
			dev_err(isp->dev,
				"atomisp_subdev_register_entities fail\n");
			क्रम (; i > 0; i--)
				atomisp_subdev_unरेजिस्टर_entities(
				    &isp->asd[i - 1]);
			जाओ subdev_रेजिस्टर_failed;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		काष्ठा atomisp_sub_device *asd = &isp->asd[i];

		init_completion(&asd->init_करोne);

		asd->delayed_init_workq =
		    alloc_workqueue(isp->v4l2_dev.name, WQ_CPU_INTENSIVE,
				    1);
		अगर (!asd->delayed_init_workq) अणु
			dev_err(isp->dev,
				"Failed to initialize delayed init workq\n");
			ret = -ENOMEM;

			क्रम (; i > 0; i--)
				destroy_workqueue(isp->asd[i - 1].
						  delayed_init_workq);
			जाओ wq_alloc_failed;
		पूर्ण
		INIT_WORK(&asd->delayed_init_work, atomisp_delayed_init_work);
	पूर्ण

	क्रम (i = 0; i < isp->input_cnt; i++) अणु
		अगर (isp->inमाला_दो[i].port >= ATOMISP_CAMERA_NR_PORTS) अणु
			dev_err(isp->dev, "isp->inputs port %d not supported\n",
				isp->inमाला_दो[i].port);
			ret = -EINVAL;
			जाओ link_failed;
		पूर्ण
	पूर्ण

	dev_dbg(isp->dev,
		"FILE_INPUT enable, camera_cnt: %d\n", isp->input_cnt);
	isp->inमाला_दो[isp->input_cnt].type = खाता_INPUT;
	isp->inमाला_दो[isp->input_cnt].port = -1;
	isp->inमाला_दो[isp->input_cnt].camera_caps =
	    atomisp_get_शेष_camera_caps();
	isp->inमाला_दो[isp->input_cnt++].camera = &isp->file_dev.sd;

	अगर (isp->input_cnt < ATOM_ISP_MAX_INPUTS) अणु
		dev_dbg(isp->dev,
			"TPG detected, camera_cnt: %d\n", isp->input_cnt);
		isp->inमाला_दो[isp->input_cnt].type = TEST_PATTERN;
		isp->inमाला_दो[isp->input_cnt].port = -1;
		isp->inमाला_दो[isp->input_cnt].camera_caps =
		    atomisp_get_शेष_camera_caps();
		isp->inमाला_दो[isp->input_cnt++].camera = &isp->tpg.sd;
	पूर्ण अन्यथा अणु
		dev_warn(isp->dev, "too many atomisp inputs, TPG ignored.\n");
	पूर्ण

	ret = v4l2_device_रेजिस्टर_subdev_nodes(&isp->v4l2_dev);
	अगर (ret < 0)
		जाओ link_failed;

	वापस media_device_रेजिस्टर(&isp->media_dev);

link_failed:
	क्रम (i = 0; i < isp->num_of_streams; i++)
		destroy_workqueue(isp->asd[i].
				  delayed_init_workq);
wq_alloc_failed:
	क्रम (i = 0; i < isp->num_of_streams; i++)
		atomisp_subdev_unरेजिस्टर_entities(
		    &isp->asd[i]);
subdev_रेजिस्टर_failed:
	atomisp_tpg_unरेजिस्टर_entities(&isp->tpg);
tpg_रेजिस्टर_failed:
	atomisp_file_input_unरेजिस्टर_entities(&isp->file_dev);
file_input_रेजिस्टर_failed:
	क्रम (i = 0; i < ATOMISP_CAMERA_NR_PORTS; i++)
		atomisp_mipi_csi2_unरेजिस्टर_entities(&isp->csi2_port[i]);
csi_and_subdev_probe_failed:
	v4l2_device_unरेजिस्टर(&isp->v4l2_dev);
v4l2_device_failed:
	media_device_unरेजिस्टर(&isp->media_dev);
	media_device_cleanup(&isp->media_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक atomisp_initialize_modules(काष्ठा atomisp_device *isp)
अणु
	पूर्णांक ret;

	ret = atomisp_mipi_csi2_init(isp);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "mipi csi2 initialization failed\n");
		जाओ error_mipi_csi2;
	पूर्ण

	ret = atomisp_file_input_init(isp);
	अगर (ret < 0) अणु
		dev_err(isp->dev,
			"file input device initialization failed\n");
		जाओ error_file_input;
	पूर्ण

	ret = atomisp_tpg_init(isp);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "tpg initialization failed\n");
		जाओ error_tpg;
	पूर्ण

	ret = atomisp_subdev_init(isp);
	अगर (ret < 0) अणु
		dev_err(isp->dev, "ISP subdev initialization failed\n");
		जाओ error_isp_subdev;
	पूर्ण

	वापस 0;

error_isp_subdev:
error_tpg:
	atomisp_tpg_cleanup(isp);
error_file_input:
	atomisp_file_input_cleanup(isp);
error_mipi_csi2:
	atomisp_mipi_csi2_cleanup(isp);
	वापस ret;
पूर्ण

अटल व्योम atomisp_uninitialize_modules(काष्ठा atomisp_device *isp)
अणु
	atomisp_tpg_cleanup(isp);
	atomisp_file_input_cleanup(isp);
	atomisp_mipi_csi2_cleanup(isp);
पूर्ण

स्थिर काष्ठा firmware *
atomisp_load_firmware(काष्ठा atomisp_device *isp)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक rc;
	अक्षर *fw_path = शून्य;

	अगर (skip_fwload)
		वापस शून्य;

	अगर (firmware_name[0] != '\0') अणु
		fw_path = firmware_name;
	पूर्ण अन्यथा अणु
		अगर ((isp->media_dev.hw_revision  >> ATOMISP_HW_REVISION_SHIFT)
		    == ATOMISP_HW_REVISION_ISP2401)
			fw_path = "shisp_2401a0_v21.bin";

		अगर (isp->media_dev.hw_revision ==
		    ((ATOMISP_HW_REVISION_ISP2401_LEGACY << ATOMISP_HW_REVISION_SHIFT)
		    | ATOMISP_HW_STEPPING_A0))
			fw_path = "shisp_2401a0_legacy_v21.bin";

		अगर (isp->media_dev.hw_revision ==
		    ((ATOMISP_HW_REVISION_ISP2400 << ATOMISP_HW_REVISION_SHIFT)
		    | ATOMISP_HW_STEPPING_B0))
			fw_path = "shisp_2400b0_v21.bin";
	पूर्ण

	अगर (!fw_path) अणु
		dev_err(isp->dev, "Unsupported hw_revision 0x%x\n",
			isp->media_dev.hw_revision);
		वापस शून्य;
	पूर्ण

	rc = request_firmware(&fw, fw_path, isp->dev);
	अगर (rc) अणु
		dev_err(isp->dev,
			"atomisp: Error %d while requesting firmware %s\n",
			rc, fw_path);
		वापस शून्य;
	पूर्ण

	वापस fw;
पूर्ण

/*
 * Check क्रम flags the driver was compiled with against the PCI
 * device. Always वापसs true on other than ISP 2400.
 */
अटल bool is_valid_device(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *product;

	product = dmi_get_प्रणाली_info(DMI_PRODUCT_NAME);

	चयन (id->device & ATOMISP_PCI_DEVICE_SOC_MASK) अणु
	हाल ATOMISP_PCI_DEVICE_SOC_MRFLD:
		name = "Merrifield";
		अवरोध;
	हाल ATOMISP_PCI_DEVICE_SOC_BYT:
		name = "Baytrail";
		अवरोध;
	हाल ATOMISP_PCI_DEVICE_SOC_ANN:
		name = "Anniedale";
		अवरोध;
	हाल ATOMISP_PCI_DEVICE_SOC_CHT:
		name = "Cherrytrail";
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "%s: unknown device ID %x04:%x04\n",
			product, id->venकरोr, id->device);
		वापस false;
	पूर्ण

	अगर (pdev->revision <= ATOMISP_PCI_REV_BYT_A0_MAX) अणु
		dev_err(&pdev->dev, "%s revision %d is not unsupported\n",
			name, pdev->revision);
		वापस false;
	पूर्ण

	/*
	 * FIXME:
	 * हटाओ the अगर once the driver become generic
	 */

#अगर defined(ISP2400)
	अगर (IS_ISP2401) अणु
		dev_err(&pdev->dev, "Support for %s (ISP2401) was disabled at compile time\n",
			name);
		वापस false;
	पूर्ण
#अन्यथा
	अगर (!IS_ISP2401) अणु
		dev_err(&pdev->dev, "Support for %s (ISP2400) was disabled at compile time\n",
			name);
		वापस false;
	पूर्ण
#पूर्ण_अगर

	dev_info(&pdev->dev, "Detected %s version %d (ISP240%c) on %s\n",
		 name, pdev->revision, IS_ISP2401 ? '1' : '0', product);

	वापस true;
पूर्ण

अटल पूर्णांक init_atomisp_wdts(काष्ठा atomisp_device *isp)
अणु
	पूर्णांक i, err;

	atomic_set(&isp->wdt_work_queued, 0);
	isp->wdt_work_queue = alloc_workqueue(isp->v4l2_dev.name, 0, 1);
	अगर (!isp->wdt_work_queue) अणु
		dev_err(isp->dev, "Failed to initialize wdt work queue\n");
		err = -ENOMEM;
		जाओ alloc_fail;
	पूर्ण
	INIT_WORK(&isp->wdt_work, atomisp_wdt_work);

	क्रम (i = 0; i < isp->num_of_streams; i++) अणु
		काष्ठा atomisp_sub_device *asd = &isp->asd[i];

		अगर (!IS_ISP2401)
			समयr_setup(&asd->wdt, atomisp_wdt, 0);
		अन्यथा अणु
			समयr_setup(&asd->video_out_capture.wdt,
				    atomisp_wdt, 0);
			समयr_setup(&asd->video_out_preview.wdt,
				    atomisp_wdt, 0);
			समयr_setup(&asd->video_out_vf.wdt, atomisp_wdt, 0);
			समयr_setup(&asd->video_out_video_capture.wdt,
				    atomisp_wdt, 0);
		पूर्ण
	पूर्ण
	वापस 0;
alloc_fail:
	वापस err;
पूर्ण

#घोषणा ATOM_ISP_PCI_BAR	0

अटल पूर्णांक atomisp_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर काष्ठा atomisp_platक्रमm_data *pdata;
	काष्ठा atomisp_device *isp;
	अचिन्हित पूर्णांक start;
	पूर्णांक err, val;
	u32 irq;

	अगर (!is_valid_device(pdev, id))
		वापस -ENODEV;

	/* Poपूर्णांकer to काष्ठा device. */
	atomisp_dev = &pdev->dev;

	pdata = atomisp_get_platक्रमm_data();
	अगर (!pdata)
		dev_warn(&pdev->dev, "no platform data available\n");

	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to enable CI ISP device (%d)\n", err);
		वापस err;
	पूर्ण

	start = pci_resource_start(pdev, ATOM_ISP_PCI_BAR);
	dev_dbg(&pdev->dev, "start: 0x%x\n", start);

	err = pcim_iomap_regions(pdev, 1 << ATOM_ISP_PCI_BAR, pci_name(pdev));
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to I/O memory remapping (%d)\n", err);
		जाओ ioremap_fail;
	पूर्ण

	isp = devm_kzalloc(&pdev->dev, माप(*isp), GFP_KERNEL);
	अगर (!isp) अणु
		err = -ENOMEM;
		जाओ atomisp_dev_alloc_fail;
	पूर्ण

	isp->dev = &pdev->dev;
	isp->base = pcim_iomap_table(pdev)[ATOM_ISP_PCI_BAR];
	isp->sw_contex.घातer_state = ATOM_ISP_POWER_UP;
	isp->saved_regs.ispmmadr = start;

	dev_dbg(&pdev->dev, "atomisp mmio base: %p\n", isp->base);

	rt_mutex_init(&isp->mutex);
	mutex_init(&isp->streamoff_mutex);
	spin_lock_init(&isp->lock);

	/* This is not a true PCI device on SoC, so the delay is not needed. */
	pdev->d3hot_delay = 0;

	pci_set_drvdata(pdev, isp);

	चयन (id->device & ATOMISP_PCI_DEVICE_SOC_MASK) अणु
	हाल ATOMISP_PCI_DEVICE_SOC_MRFLD:
		isp->media_dev.hw_revision =
		    (ATOMISP_HW_REVISION_ISP2400
		     << ATOMISP_HW_REVISION_SHIFT) |
		    ATOMISP_HW_STEPPING_B0;

		चयन (id->device) अणु
		हाल ATOMISP_PCI_DEVICE_SOC_MRFLD_1179:
			isp->dfs = &dfs_config_merr_1179;
			अवरोध;
		हाल ATOMISP_PCI_DEVICE_SOC_MRFLD_117A:
			isp->dfs = &dfs_config_merr_117a;

			अवरोध;
		शेष:
			isp->dfs = &dfs_config_merr;
			अवरोध;
		पूर्ण
		isp->hpll_freq = HPLL_FREQ_1600MHZ;
		अवरोध;
	हाल ATOMISP_PCI_DEVICE_SOC_BYT:
		isp->media_dev.hw_revision =
		    (ATOMISP_HW_REVISION_ISP2400
		     << ATOMISP_HW_REVISION_SHIFT) |
		    ATOMISP_HW_STEPPING_B0;

		/*
		 * Note: some Intel-based tablets with Android use a dअगरferent
		 * DFS table. Based on the comments at the Yocto Aero meta
		 * version of this driver (at the ssid.h header), they're
		 * identअगरied via a "spid" var:
		 *
		 *	androidboot.spid=vend:cust:manu:plat:prod:hard
		 *
		 * As we करोn't have this upstream, nor we know enough details
		 * to use a DMI or PCI match table, the old code was just
		 * हटाओd, but let's keep a note here as a reminder that,
		 * क्रम certain devices, we may need to limit the max DFS
		 * frequency to be below certain values, adjusting the
		 * resolution accordingly.
		 */
		isp->dfs = &dfs_config_byt;

		/*
		 * HPLL frequency is known to be device-specअगरic, but we करोn't
		 * have specs yet क्रम exactly how it varies.  Default to
		 * BYT-CR but let provisioning set it via EFI variable
		 */
		isp->hpll_freq = gmin_get_var_पूर्णांक(&pdev->dev, false, "HpllFreq", HPLL_FREQ_2000MHZ);

		/*
		 * क्रम BYT/CHT we are put isp पूर्णांकo D3cold to aव्योम pci रेजिस्टरs access
		 * in घातer off. Set d3cold_delay to 0 since शेष 100ms is not
		 * necessary.
		 */
		pdev->d3cold_delay = 0;
		अवरोध;
	हाल ATOMISP_PCI_DEVICE_SOC_ANN:
		isp->media_dev.hw_revision = (
#अगर_घोषित ISP2401_NEW_INPUT_SYSTEM
						 ATOMISP_HW_REVISION_ISP2401
#अन्यथा
						 ATOMISP_HW_REVISION_ISP2401_LEGACY
#पूर्ण_अगर
						 << ATOMISP_HW_REVISION_SHIFT);
		isp->media_dev.hw_revision |= pdev->revision < 2 ?
					      ATOMISP_HW_STEPPING_A0 : ATOMISP_HW_STEPPING_B0;
		isp->dfs = &dfs_config_merr;
		isp->hpll_freq = HPLL_FREQ_1600MHZ;
		अवरोध;
	हाल ATOMISP_PCI_DEVICE_SOC_CHT:
		isp->media_dev.hw_revision = (
#अगर_घोषित ISP2401_NEW_INPUT_SYSTEM
						 ATOMISP_HW_REVISION_ISP2401
#अन्यथा
						 ATOMISP_HW_REVISION_ISP2401_LEGACY
#पूर्ण_अगर
						 << ATOMISP_HW_REVISION_SHIFT);
		isp->media_dev.hw_revision |= pdev->revision < 2 ?
					      ATOMISP_HW_STEPPING_A0 : ATOMISP_HW_STEPPING_B0;

		isp->dfs = &dfs_config_cht;
		pdev->d3cold_delay = 0;

		iosf_mbi_पढ़ो(BT_MBI_UNIT_CCK, MBI_REG_READ, CCK_FUSE_REG_0, &val);
		चयन (val & CCK_FUSE_HPLL_FREQ_MASK) अणु
		हाल 0x00:
			isp->hpll_freq = HPLL_FREQ_800MHZ;
			अवरोध;
		हाल 0x01:
			isp->hpll_freq = HPLL_FREQ_1600MHZ;
			अवरोध;
		हाल 0x02:
			isp->hpll_freq = HPLL_FREQ_2000MHZ;
			अवरोध;
		शेष:
			isp->hpll_freq = HPLL_FREQ_1600MHZ;
			dev_warn(&pdev->dev, "read HPLL from cck failed. Default to 1600 MHz.\n");
		पूर्ण
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "un-supported IUNIT device\n");
		err = -ENODEV;
		जाओ atomisp_dev_alloc_fail;
	पूर्ण

	dev_info(&pdev->dev, "ISP HPLL frequency base = %d MHz\n", isp->hpll_freq);

	isp->max_isr_latency = ATOMISP_MAX_ISR_LATENCY;

	/* Load isp firmware from user space */
	अगर (!defer_fw_load) अणु
		isp->firmware = atomisp_load_firmware(isp);
		अगर (!isp->firmware) अणु
			err = -ENOENT;
			dev_dbg(&pdev->dev, "Firmware load failed\n");
			जाओ load_fw_fail;
		पूर्ण

		err = sh_css_check_firmware_version(isp->dev, isp->firmware->data);
		अगर (err) अणु
			dev_dbg(&pdev->dev, "Firmware version check failed\n");
			जाओ fw_validation_fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info(&pdev->dev, "Firmware load will be deferred\n");
	पूर्ण

	pci_set_master(pdev);

	err = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSI);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "Failed to enable msi (%d)\n", err);
		जाओ enable_msi_fail;
	पूर्ण

	atomisp_msi_irq_init(isp);

	cpu_latency_qos_add_request(&isp->pm_qos, PM_QOS_DEFAULT_VALUE);

	/*
	 * क्रम MRFLD, Software/firmware needs to ग_लिखो a 1 to bit 0 of
	 * the रेजिस्टर at CSI_RECEIVER_SELECTION_REG to enable SH CSI
	 * backend ग_लिखो 0 will enable Arasan CSI backend, which has
	 * bugs(like sighting:4567697 and 4567699) and will be हटाओd
	 * in B0
	 */
	atomisp_css2_hw_store_32(MRFLD_CSI_RECEIVER_SELECTION_REG, 1);

	अगर ((id->device & ATOMISP_PCI_DEVICE_SOC_MASK) ==
	    ATOMISP_PCI_DEVICE_SOC_MRFLD) अणु
		u32 csi_afe_trim;

		/*
		 * Workaround क्रम imbalance data eye issue which is observed
		 * on TNG B0.
		 */
		pci_पढ़ो_config_dword(pdev, MRFLD_PCI_CSI_AFE_TRIM_CONTROL, &csi_afe_trim);
		csi_afe_trim &= ~((MRFLD_PCI_CSI_HSRXCLKTRIM_MASK <<
				   MRFLD_PCI_CSI1_HSRXCLKTRIM_SHIFT) |
				  (MRFLD_PCI_CSI_HSRXCLKTRIM_MASK <<
				   MRFLD_PCI_CSI2_HSRXCLKTRIM_SHIFT) |
				  (MRFLD_PCI_CSI_HSRXCLKTRIM_MASK <<
				   MRFLD_PCI_CSI3_HSRXCLKTRIM_SHIFT));
		csi_afe_trim |= (MRFLD_PCI_CSI1_HSRXCLKTRIM <<
				 MRFLD_PCI_CSI1_HSRXCLKTRIM_SHIFT) |
				(MRFLD_PCI_CSI2_HSRXCLKTRIM <<
				 MRFLD_PCI_CSI2_HSRXCLKTRIM_SHIFT) |
				(MRFLD_PCI_CSI3_HSRXCLKTRIM <<
				 MRFLD_PCI_CSI3_HSRXCLKTRIM_SHIFT);
		pci_ग_लिखो_config_dword(pdev, MRFLD_PCI_CSI_AFE_TRIM_CONTROL, csi_afe_trim);
	पूर्ण

	err = atomisp_initialize_modules(isp);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "atomisp_initialize_modules (%d)\n", err);
		जाओ initialize_modules_fail;
	पूर्ण

	err = atomisp_रेजिस्टर_entities(isp);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "atomisp_register_entities failed (%d)\n", err);
		जाओ रेजिस्टर_entities_fail;
	पूर्ण
	err = atomisp_create_pads_links(isp);
	अगर (err < 0)
		जाओ रेजिस्टर_entities_fail;
	/* init atomisp wdts */
	अगर (init_atomisp_wdts(isp) != 0)
		जाओ wdt_work_queue_fail;

	/* save the iunit context only once after all the values are init'ed. */
	atomisp_save_iunit_reg(isp);

	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_allow(&pdev->dev);

	hmm_init_mem_stat(repool_pgnr, dypool_enable, dypool_pgnr);
	err = hmm_pool_रेजिस्टर(repool_pgnr, HMM_POOL_TYPE_RESERVED);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register reserved memory pool.\n");
		जाओ hmm_pool_fail;
	पूर्ण

	/* Init ISP memory management */
	hmm_init();

	err = devm_request_thपढ़ोed_irq(&pdev->dev, pdev->irq,
					atomisp_isr, atomisp_isr_thपढ़ो,
					IRQF_SHARED, "isp_irq", isp);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to request irq (%d)\n", err);
		जाओ request_irq_fail;
	पूर्ण

	/* Load firmware पूर्णांकo ISP memory */
	अगर (!defer_fw_load) अणु
		err = atomisp_css_load_firmware(isp);
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to init css.\n");
			जाओ css_init_fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(&pdev->dev, "Skip css init.\n");
	पूर्ण
	/* Clear FW image from memory */
	release_firmware(isp->firmware);
	isp->firmware = शून्य;
	isp->css_env.isp_css_fw.data = शून्य;

	atomisp_drvfs_init(isp);

	वापस 0;

css_init_fail:
	devm_मुक्त_irq(&pdev->dev, pdev->irq, isp);
request_irq_fail:
	hmm_cleanup();
	hmm_pool_unरेजिस्टर(HMM_POOL_TYPE_RESERVED);
hmm_pool_fail:
	destroy_workqueue(isp->wdt_work_queue);
wdt_work_queue_fail:
	atomisp_acc_cleanup(isp);
	atomisp_unरेजिस्टर_entities(isp);
रेजिस्टर_entities_fail:
	atomisp_uninitialize_modules(isp);
initialize_modules_fail:
	cpu_latency_qos_हटाओ_request(&isp->pm_qos);
	atomisp_msi_irq_uninit(isp);
	pci_मुक्त_irq_vectors(pdev);
enable_msi_fail:
fw_validation_fail:
	release_firmware(isp->firmware);
load_fw_fail:
	/*
	 * Switch off ISP, as keeping it घातered on would prevent
	 * reaching S0ix states.
	 *
	 * The following lines have been copied from atomisp suspend path
	 */

	pci_पढ़ो_config_dword(pdev, PCI_INTERRUPT_CTRL, &irq);
	irq = irq & 1 << INTR_IIR;
	pci_ग_लिखो_config_dword(pdev, PCI_INTERRUPT_CTRL, irq);

	pci_पढ़ो_config_dword(pdev, PCI_INTERRUPT_CTRL, &irq);
	irq &= ~(1 << INTR_IER);
	pci_ग_लिखो_config_dword(pdev, PCI_INTERRUPT_CTRL, irq);

	atomisp_msi_irq_uninit(isp);

	atomisp_ospm_dphy_करोwn(isp);

	/* Address later when we worry about the ...field chips */
	अगर (IS_ENABLED(CONFIG_PM) && atomisp_mrfld_घातer_करोwn(isp))
		dev_err(&pdev->dev, "Failed to switch off ISP\n");

atomisp_dev_alloc_fail:
	pcim_iounmap_regions(pdev, 1 << ATOM_ISP_PCI_BAR);

ioremap_fail:
	वापस err;
पूर्ण

अटल व्योम atomisp_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा atomisp_device *isp = pci_get_drvdata(pdev);

	dev_info(&pdev->dev, "Removing atomisp driver\n");

	atomisp_drvfs_निकास();

	atomisp_acc_cleanup(isp);

	ia_css_unload_firmware();
	hmm_cleanup();

	pm_runसमय_क्रमbid(&pdev->dev);
	pm_runसमय_get_noresume(&pdev->dev);
	cpu_latency_qos_हटाओ_request(&isp->pm_qos);

	atomisp_msi_irq_uninit(isp);
	atomisp_unरेजिस्टर_entities(isp);

	destroy_workqueue(isp->wdt_work_queue);
	atomisp_file_input_cleanup(isp);

	release_firmware(isp->firmware);

	hmm_pool_unरेजिस्टर(HMM_POOL_TYPE_RESERVED);
पूर्ण

अटल स्थिर काष्ठा pci_device_id atomisp_pci_tbl[] = अणु
	/* Merrअगरield */
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, ATOMISP_PCI_DEVICE_SOC_MRFLD)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, ATOMISP_PCI_DEVICE_SOC_MRFLD_1179)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, ATOMISP_PCI_DEVICE_SOC_MRFLD_117A)पूर्ण,
	/* Baytrail */
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, ATOMISP_PCI_DEVICE_SOC_BYT)पूर्ण,
	/* Anniedale (Merrअगरield+ / Moorefield) */
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, ATOMISP_PCI_DEVICE_SOC_ANN)पूर्ण,
	/* Cherrytrail */
	अणुPCI_DEVICE(PCI_VENDOR_ID_INTEL, ATOMISP_PCI_DEVICE_SOC_CHT)पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, atomisp_pci_tbl);

अटल स्थिर काष्ठा dev_pm_ops atomisp_pm_ops = अणु
	.runसमय_suspend = atomisp_runसमय_suspend,
	.runसमय_resume = atomisp_runसमय_resume,
	.suspend = atomisp_suspend,
	.resume = atomisp_resume,
पूर्ण;

अटल काष्ठा pci_driver atomisp_pci_driver = अणु
	.driver = अणु
		.pm = &atomisp_pm_ops,
	पूर्ण,
	.name = "atomisp-isp2",
	.id_table = atomisp_pci_tbl,
	.probe = atomisp_pci_probe,
	.हटाओ = atomisp_pci_हटाओ,
पूर्ण;

module_pci_driver(atomisp_pci_driver);

MODULE_AUTHOR("Wen Wang <wen.w.wang@intel.com>");
MODULE_AUTHOR("Xiaolin Zhang <xiaolin.zhang@intel.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Intel ATOM Platform ISP Driver");
