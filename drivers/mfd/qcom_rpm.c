<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, Sony Mobile Communications AB.
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 * Author: Bjorn Andersson <bjorn.andersson@sonymobile.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/qcom_rpm.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/clk.h>

#समावेश <dt-bindings/mfd/qcom-rpm.h>

काष्ठा qcom_rpm_resource अणु
	अचिन्हित target_id;
	अचिन्हित status_id;
	अचिन्हित select_id;
	अचिन्हित size;
पूर्ण;

काष्ठा qcom_rpm_data अणु
	u32 version;
	स्थिर काष्ठा qcom_rpm_resource *resource_table;
	अचिन्हित पूर्णांक n_resources;
	अचिन्हित पूर्णांक req_ctx_off;
	अचिन्हित पूर्णांक req_sel_off;
	अचिन्हित पूर्णांक ack_ctx_off;
	अचिन्हित पूर्णांक ack_sel_off;
	अचिन्हित पूर्णांक req_sel_size;
	अचिन्हित पूर्णांक ack_sel_size;
पूर्ण;

काष्ठा qcom_rpm अणु
	काष्ठा device *dev;
	काष्ठा regmap *ipc_regmap;
	अचिन्हित ipc_offset;
	अचिन्हित ipc_bit;
	काष्ठा clk *ramclk;

	काष्ठा completion ack;
	काष्ठा mutex lock;

	व्योम __iomem *status_regs;
	व्योम __iomem *ctrl_regs;
	व्योम __iomem *req_regs;

	u32 ack_status;

	स्थिर काष्ठा qcom_rpm_data *data;
पूर्ण;

#घोषणा RPM_STATUS_REG(rpm, i)	((rpm)->status_regs + (i) * 4)
#घोषणा RPM_CTRL_REG(rpm, i)	((rpm)->ctrl_regs + (i) * 4)
#घोषणा RPM_REQ_REG(rpm, i)	((rpm)->req_regs + (i) * 4)

#घोषणा RPM_REQUEST_TIMEOUT	(5 * HZ)

#घोषणा RPM_MAX_SEL_SIZE	7

#घोषणा RPM_NOTIFICATION	BIT(30)
#घोषणा RPM_REJECTED		BIT(31)

अटल स्थिर काष्ठा qcom_rpm_resource apq8064_rpm_resource_table[] = अणु
	[QCOM_RPM_CXO_CLK] =			अणु 25, 9, 5, 1 पूर्ण,
	[QCOM_RPM_PXO_CLK] =			अणु 26, 10, 6, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_CLK] =		अणु 27, 11, 8, 1 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_CLK] =		अणु 28, 12, 9, 1 पूर्ण,
	[QCOM_RPM_MM_FABRIC_CLK] =		अणु 29, 13, 10, 1 पूर्ण,
	[QCOM_RPM_DAYTONA_FABRIC_CLK] =		अणु 30, 14, 11, 1 पूर्ण,
	[QCOM_RPM_SFPB_CLK] =			अणु 31, 15, 12, 1 पूर्ण,
	[QCOM_RPM_CFPB_CLK] =			अणु 32, 16, 13, 1 पूर्ण,
	[QCOM_RPM_MMFPB_CLK] =			अणु 33, 17, 14, 1 पूर्ण,
	[QCOM_RPM_EBI1_CLK] =			अणु 34, 18, 16, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_HALT] =		अणु 35, 19, 18, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_MODE] =		अणु 37, 20, 19, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_IOCTL] =		अणु 40, 21, 20, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_ARB] =		अणु 41, 22, 21, 12 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_HALT] =		अणु 53, 23, 22, 1 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_MODE] =		अणु 55, 24, 23, 1 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_IOCTL] =		अणु 58, 25, 24, 1 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_ARB] =		अणु 59, 26, 25, 30 पूर्ण,
	[QCOM_RPM_MM_FABRIC_HALT] =		अणु 89, 27, 26, 1 पूर्ण,
	[QCOM_RPM_MM_FABRIC_MODE] =		अणु 91, 28, 27, 1 पूर्ण,
	[QCOM_RPM_MM_FABRIC_IOCTL] =		अणु 94, 29, 28, 1 पूर्ण,
	[QCOM_RPM_MM_FABRIC_ARB] =		अणु 95, 30, 29, 21 पूर्ण,
	[QCOM_RPM_PM8921_SMPS1] =		अणु 116, 31, 30, 2 पूर्ण,
	[QCOM_RPM_PM8921_SMPS2] =		अणु 118, 33, 31, 2 पूर्ण,
	[QCOM_RPM_PM8921_SMPS3] =		अणु 120, 35, 32, 2 पूर्ण,
	[QCOM_RPM_PM8921_SMPS4] =		अणु 122, 37, 33, 2 पूर्ण,
	[QCOM_RPM_PM8921_SMPS5] =		अणु 124, 39, 34, 2 पूर्ण,
	[QCOM_RPM_PM8921_SMPS6] =		अणु 126, 41, 35, 2 पूर्ण,
	[QCOM_RPM_PM8921_SMPS7] =		अणु 128, 43, 36, 2 पूर्ण,
	[QCOM_RPM_PM8921_SMPS8] =		अणु 130, 45, 37, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO1] =		अणु 132, 47, 38, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO2] =		अणु 134, 49, 39, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO3] =		अणु 136, 51, 40, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO4] =		अणु 138, 53, 41, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO5] =		अणु 140, 55, 42, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO6] =		अणु 142, 57, 43, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO7] =		अणु 144, 59, 44, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO8] =		अणु 146, 61, 45, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO9] =		अणु 148, 63, 46, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO10] =		अणु 150, 65, 47, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO11] =		अणु 152, 67, 48, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO12] =		अणु 154, 69, 49, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO13] =		अणु 156, 71, 50, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO14] =		अणु 158, 73, 51, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO15] =		अणु 160, 75, 52, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO16] =		अणु 162, 77, 53, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO17] =		अणु 164, 79, 54, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO18] =		अणु 166, 81, 55, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO19] =		अणु 168, 83, 56, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO20] =		अणु 170, 85, 57, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO21] =		अणु 172, 87, 58, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO22] =		अणु 174, 89, 59, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO23] =		अणु 176, 91, 60, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO24] =		अणु 178, 93, 61, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO25] =		अणु 180, 95, 62, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO26] =		अणु 182, 97, 63, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO27] =		अणु 184, 99, 64, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO28] =		अणु 186, 101, 65, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO29] =		अणु 188, 103, 66, 2 पूर्ण,
	[QCOM_RPM_PM8921_CLK1] =		अणु 190, 105, 67, 2 पूर्ण,
	[QCOM_RPM_PM8921_CLK2] =		अणु 192, 107, 68, 2 पूर्ण,
	[QCOM_RPM_PM8921_LVS1] =		अणु 194, 109, 69, 1 पूर्ण,
	[QCOM_RPM_PM8921_LVS2] =		अणु 195, 110, 70, 1 पूर्ण,
	[QCOM_RPM_PM8921_LVS3] =		अणु 196, 111, 71, 1 पूर्ण,
	[QCOM_RPM_PM8921_LVS4] =		अणु 197, 112, 72, 1 पूर्ण,
	[QCOM_RPM_PM8921_LVS5] =		अणु 198, 113, 73, 1 पूर्ण,
	[QCOM_RPM_PM8921_LVS6] =		अणु 199, 114, 74, 1 पूर्ण,
	[QCOM_RPM_PM8921_LVS7] =		अणु 200, 115, 75, 1 पूर्ण,
	[QCOM_RPM_PM8821_SMPS1] =		अणु 201, 116, 76, 2 पूर्ण,
	[QCOM_RPM_PM8821_SMPS2] =		अणु 203, 118, 77, 2 पूर्ण,
	[QCOM_RPM_PM8821_LDO1] =		अणु 205, 120, 78, 2 पूर्ण,
	[QCOM_RPM_PM8921_NCP] =			अणु 207, 122, 80, 2 पूर्ण,
	[QCOM_RPM_CXO_BUFFERS] =		अणु 209, 124, 81, 1 पूर्ण,
	[QCOM_RPM_USB_OTG_SWITCH] =		अणु 210, 125, 82, 1 पूर्ण,
	[QCOM_RPM_HDMI_SWITCH] =		अणु 211, 126, 83, 1 पूर्ण,
	[QCOM_RPM_DDR_DMM] =			अणु 212, 127, 84, 2 पूर्ण,
	[QCOM_RPM_QDSS_CLK] =			अणु 214, ~0, 7, 1 पूर्ण,
	[QCOM_RPM_VDDMIN_GPIO] =		अणु 215, 131, 89, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_data apq8064_ढाँचा = अणु
	.version = 3,
	.resource_table = apq8064_rpm_resource_table,
	.n_resources = ARRAY_SIZE(apq8064_rpm_resource_table),
	.req_ctx_off = 3,
	.req_sel_off = 11,
	.ack_ctx_off = 15,
	.ack_sel_off = 23,
	.req_sel_size = 4,
	.ack_sel_size = 7,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_resource msm8660_rpm_resource_table[] = अणु
	[QCOM_RPM_CXO_CLK] =			अणु 32, 12, 5, 1 पूर्ण,
	[QCOM_RPM_PXO_CLK] =			अणु 33, 13, 6, 1 पूर्ण,
	[QCOM_RPM_PLL_4] =			अणु 34, 14, 7, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_CLK] =		अणु 35, 15, 8, 1 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_CLK] =		अणु 36, 16, 9, 1 पूर्ण,
	[QCOM_RPM_MM_FABRIC_CLK] =		अणु 37, 17, 10, 1 पूर्ण,
	[QCOM_RPM_DAYTONA_FABRIC_CLK] =		अणु 38, 18, 11, 1 पूर्ण,
	[QCOM_RPM_SFPB_CLK] =			अणु 39, 19, 12, 1 पूर्ण,
	[QCOM_RPM_CFPB_CLK] =			अणु 40, 20, 13, 1 पूर्ण,
	[QCOM_RPM_MMFPB_CLK] =			अणु 41, 21, 14, 1 पूर्ण,
	[QCOM_RPM_SMI_CLK] =			अणु 42, 22, 15, 1 पूर्ण,
	[QCOM_RPM_EBI1_CLK] =			अणु 43, 23, 16, 1 पूर्ण,
	[QCOM_RPM_APPS_L2_CACHE_CTL] =		अणु 44, 24, 17, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_HALT] =		अणु 45, 25, 18, 2 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_MODE] =		अणु 47, 26, 19, 3 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_ARB] =		अणु 51, 28, 21, 6 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_HALT] =		अणु 63, 29, 22, 2 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_MODE] =		अणु 65, 30, 23, 3 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_ARB] =		अणु 69, 32, 25, 22 पूर्ण,
	[QCOM_RPM_MM_FABRIC_HALT] =		अणु 105, 33, 26, 2 पूर्ण,
	[QCOM_RPM_MM_FABRIC_MODE] =		अणु 107, 34, 27, 3 पूर्ण,
	[QCOM_RPM_MM_FABRIC_ARB] =		अणु 111, 36, 29, 23 पूर्ण,
	[QCOM_RPM_PM8901_SMPS0] =		अणु 134, 37, 30, 2 पूर्ण,
	[QCOM_RPM_PM8901_SMPS1] =		अणु 136, 39, 31, 2 पूर्ण,
	[QCOM_RPM_PM8901_SMPS2] =		अणु 138, 41, 32, 2 पूर्ण,
	[QCOM_RPM_PM8901_SMPS3] =		अणु 140, 43, 33, 2 पूर्ण,
	[QCOM_RPM_PM8901_SMPS4] =		अणु 142, 45, 34, 2 पूर्ण,
	[QCOM_RPM_PM8901_LDO0] =		अणु 144, 47, 35, 2 पूर्ण,
	[QCOM_RPM_PM8901_LDO1] =		अणु 146, 49, 36, 2 पूर्ण,
	[QCOM_RPM_PM8901_LDO2] =		अणु 148, 51, 37, 2 पूर्ण,
	[QCOM_RPM_PM8901_LDO3] =		अणु 150, 53, 38, 2 पूर्ण,
	[QCOM_RPM_PM8901_LDO4] =		अणु 152, 55, 39, 2 पूर्ण,
	[QCOM_RPM_PM8901_LDO5] =		अणु 154, 57, 40, 2 पूर्ण,
	[QCOM_RPM_PM8901_LDO6] =		अणु 156, 59, 41, 2 पूर्ण,
	[QCOM_RPM_PM8901_LVS0] =		अणु 158, 61, 42, 1 पूर्ण,
	[QCOM_RPM_PM8901_LVS1] =		अणु 159, 62, 43, 1 पूर्ण,
	[QCOM_RPM_PM8901_LVS2] =		अणु 160, 63, 44, 1 पूर्ण,
	[QCOM_RPM_PM8901_LVS3] =		अणु 161, 64, 45, 1 पूर्ण,
	[QCOM_RPM_PM8901_MVS] =			अणु 162, 65, 46, 1 पूर्ण,
	[QCOM_RPM_PM8058_SMPS0] =		अणु 163, 66, 47, 2 पूर्ण,
	[QCOM_RPM_PM8058_SMPS1] =		अणु 165, 68, 48, 2 पूर्ण,
	[QCOM_RPM_PM8058_SMPS2] =		अणु 167, 70, 49, 2 पूर्ण,
	[QCOM_RPM_PM8058_SMPS3] =		अणु 169, 72, 50, 2 पूर्ण,
	[QCOM_RPM_PM8058_SMPS4] =		अणु 171, 74, 51, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO0] =		अणु 173, 76, 52, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO1] =		अणु 175, 78, 53, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO2] =		अणु 177, 80, 54, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO3] =		अणु 179, 82, 55, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO4] =		अणु 181, 84, 56, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO5] =		अणु 183, 86, 57, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO6] =		अणु 185, 88, 58, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO7] =		अणु 187, 90, 59, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO8] =		अणु 189, 92, 60, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO9] =		अणु 191, 94, 61, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO10] =		अणु 193, 96, 62, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO11] =		अणु 195, 98, 63, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO12] =		अणु 197, 100, 64, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO13] =		अणु 199, 102, 65, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO14] =		अणु 201, 104, 66, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO15] =		अणु 203, 106, 67, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO16] =		अणु 205, 108, 68, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO17] =		अणु 207, 110, 69, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO18] =		अणु 209, 112, 70, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO19] =		अणु 211, 114, 71, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO20] =		अणु 213, 116, 72, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO21] =		अणु 215, 118, 73, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO22] =		अणु 217, 120, 74, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO23] =		अणु 219, 122, 75, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO24] =		अणु 221, 124, 76, 2 पूर्ण,
	[QCOM_RPM_PM8058_LDO25] =		अणु 223, 126, 77, 2 पूर्ण,
	[QCOM_RPM_PM8058_LVS0] =		अणु 225, 128, 78, 1 पूर्ण,
	[QCOM_RPM_PM8058_LVS1] =		अणु 226, 129, 79, 1 पूर्ण,
	[QCOM_RPM_PM8058_NCP] =			अणु 227, 130, 80, 2 पूर्ण,
	[QCOM_RPM_CXO_BUFFERS] =		अणु 229, 132, 81, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_data msm8660_ढाँचा = अणु
	.version = 2,
	.resource_table = msm8660_rpm_resource_table,
	.n_resources = ARRAY_SIZE(msm8660_rpm_resource_table),
	.req_ctx_off = 3,
	.req_sel_off = 11,
	.ack_ctx_off = 19,
	.ack_sel_off = 27,
	.req_sel_size = 7,
	.ack_sel_size = 7,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_resource msm8960_rpm_resource_table[] = अणु
	[QCOM_RPM_CXO_CLK] =			अणु 25, 9, 5, 1 पूर्ण,
	[QCOM_RPM_PXO_CLK] =			अणु 26, 10, 6, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_CLK] =		अणु 27, 11, 8, 1 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_CLK] =		अणु 28, 12, 9, 1 पूर्ण,
	[QCOM_RPM_MM_FABRIC_CLK] =		अणु 29, 13, 10, 1 पूर्ण,
	[QCOM_RPM_DAYTONA_FABRIC_CLK] =		अणु 30, 14, 11, 1 पूर्ण,
	[QCOM_RPM_SFPB_CLK] =			अणु 31, 15, 12, 1 पूर्ण,
	[QCOM_RPM_CFPB_CLK] =			अणु 32, 16, 13, 1 पूर्ण,
	[QCOM_RPM_MMFPB_CLK] =			अणु 33, 17, 14, 1 पूर्ण,
	[QCOM_RPM_EBI1_CLK] =			अणु 34, 18, 16, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_HALT] =		अणु 35, 19, 18, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_MODE] =		अणु 37, 20, 19, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_IOCTL] =		अणु 40, 21, 20, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_ARB] =		अणु 41, 22, 21, 12 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_HALT] =		अणु 53, 23, 22, 1 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_MODE] =		अणु 55, 24, 23, 1 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_IOCTL] =		अणु 58, 25, 24, 1 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_ARB] =		अणु 59, 26, 25, 29 पूर्ण,
	[QCOM_RPM_MM_FABRIC_HALT] =		अणु 88, 27, 26, 1 पूर्ण,
	[QCOM_RPM_MM_FABRIC_MODE] =		अणु 90, 28, 27, 1 पूर्ण,
	[QCOM_RPM_MM_FABRIC_IOCTL] =		अणु 93, 29, 28, 1 पूर्ण,
	[QCOM_RPM_MM_FABRIC_ARB] =		अणु 94, 30, 29, 23 पूर्ण,
	[QCOM_RPM_PM8921_SMPS1] =		अणु 117, 31, 30, 2 पूर्ण,
	[QCOM_RPM_PM8921_SMPS2] =		अणु 119, 33, 31, 2 पूर्ण,
	[QCOM_RPM_PM8921_SMPS3] =		अणु 121, 35, 32, 2 पूर्ण,
	[QCOM_RPM_PM8921_SMPS4] =		अणु 123, 37, 33, 2 पूर्ण,
	[QCOM_RPM_PM8921_SMPS5] =		अणु 125, 39, 34, 2 पूर्ण,
	[QCOM_RPM_PM8921_SMPS6] =		अणु 127, 41, 35, 2 पूर्ण,
	[QCOM_RPM_PM8921_SMPS7] =		अणु 129, 43, 36, 2 पूर्ण,
	[QCOM_RPM_PM8921_SMPS8] =		अणु 131, 45, 37, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO1] =		अणु 133, 47, 38, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO2] =		अणु 135, 49, 39, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO3] =		अणु 137, 51, 40, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO4] =		अणु 139, 53, 41, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO5] =		अणु 141, 55, 42, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO6] =		अणु 143, 57, 43, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO7] =		अणु 145, 59, 44, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO8] =		अणु 147, 61, 45, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO9] =		अणु 149, 63, 46, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO10] =		अणु 151, 65, 47, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO11] =		अणु 153, 67, 48, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO12] =		अणु 155, 69, 49, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO13] =		अणु 157, 71, 50, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO14] =		अणु 159, 73, 51, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO15] =		अणु 161, 75, 52, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO16] =		अणु 163, 77, 53, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO17] =		अणु 165, 79, 54, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO18] =		अणु 167, 81, 55, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO19] =		अणु 169, 83, 56, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO20] =		अणु 171, 85, 57, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO21] =		अणु 173, 87, 58, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO22] =		अणु 175, 89, 59, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO23] =		अणु 177, 91, 60, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO24] =		अणु 179, 93, 61, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO25] =		अणु 181, 95, 62, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO26] =		अणु 183, 97, 63, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO27] =		अणु 185, 99, 64, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO28] =		अणु 187, 101, 65, 2 पूर्ण,
	[QCOM_RPM_PM8921_LDO29] =		अणु 189, 103, 66, 2 पूर्ण,
	[QCOM_RPM_PM8921_CLK1] =		अणु 191, 105, 67, 2 पूर्ण,
	[QCOM_RPM_PM8921_CLK2] =		अणु 193, 107, 68, 2 पूर्ण,
	[QCOM_RPM_PM8921_LVS1] =		अणु 195, 109, 69, 1 पूर्ण,
	[QCOM_RPM_PM8921_LVS2] =		अणु 196, 110, 70, 1 पूर्ण,
	[QCOM_RPM_PM8921_LVS3] =		अणु 197, 111, 71, 1 पूर्ण,
	[QCOM_RPM_PM8921_LVS4] =		अणु 198, 112, 72, 1 पूर्ण,
	[QCOM_RPM_PM8921_LVS5] =		अणु 199, 113, 73, 1 पूर्ण,
	[QCOM_RPM_PM8921_LVS6] =		अणु 200, 114, 74, 1 पूर्ण,
	[QCOM_RPM_PM8921_LVS7] =		अणु 201, 115, 75, 1 पूर्ण,
	[QCOM_RPM_PM8921_NCP] =			अणु 202, 116, 80, 2 पूर्ण,
	[QCOM_RPM_CXO_BUFFERS] =		अणु 204, 118, 81, 1 पूर्ण,
	[QCOM_RPM_USB_OTG_SWITCH] =		अणु 205, 119, 82, 1 पूर्ण,
	[QCOM_RPM_HDMI_SWITCH] =		अणु 206, 120, 83, 1 पूर्ण,
	[QCOM_RPM_DDR_DMM] =			अणु 207, 121, 84, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_data msm8960_ढाँचा = अणु
	.version = 3,
	.resource_table = msm8960_rpm_resource_table,
	.n_resources = ARRAY_SIZE(msm8960_rpm_resource_table),
	.req_ctx_off = 3,
	.req_sel_off = 11,
	.ack_ctx_off = 15,
	.ack_sel_off = 23,
	.req_sel_size = 4,
	.ack_sel_size = 7,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_resource ipq806x_rpm_resource_table[] = अणु
	[QCOM_RPM_CXO_CLK] =			अणु 25, 9, 5, 1 पूर्ण,
	[QCOM_RPM_PXO_CLK] =			अणु 26, 10, 6, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_CLK] =		अणु 27, 11, 8, 1 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_CLK] =		अणु 28, 12, 9, 1 पूर्ण,
	[QCOM_RPM_NSS_FABRIC_0_CLK] =		अणु 29, 13, 10, 1 पूर्ण,
	[QCOM_RPM_DAYTONA_FABRIC_CLK] =		अणु 30, 14, 11, 1 पूर्ण,
	[QCOM_RPM_SFPB_CLK] =			अणु 31, 15, 12, 1 पूर्ण,
	[QCOM_RPM_CFPB_CLK] =			अणु 32, 16, 13, 1 पूर्ण,
	[QCOM_RPM_NSS_FABRIC_1_CLK] =		अणु 33, 17, 14, 1 पूर्ण,
	[QCOM_RPM_EBI1_CLK] =			अणु 34, 18, 16, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_HALT] =		अणु 35, 19, 18, 2 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_MODE] =		अणु 37, 20, 19, 3 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_IOCTL] =		अणु 40, 21, 20, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_ARB] =		अणु 41, 22, 21, 12 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_HALT] =		अणु 53, 23, 22, 2 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_MODE] =		अणु 55, 24, 23, 3 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_IOCTL] =		अणु 58, 25, 24, 1 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_ARB] =		अणु 59, 26, 25, 30 पूर्ण,
	[QCOM_RPM_MM_FABRIC_HALT] =		अणु 89, 27, 26, 2 पूर्ण,
	[QCOM_RPM_MM_FABRIC_MODE] =		अणु 91, 28, 27, 3 पूर्ण,
	[QCOM_RPM_MM_FABRIC_IOCTL] =		अणु 94, 29, 28, 1 पूर्ण,
	[QCOM_RPM_MM_FABRIC_ARB] =		अणु 95, 30, 29, 2 पूर्ण,
	[QCOM_RPM_CXO_BUFFERS] =		अणु 209, 33, 31, 1 पूर्ण,
	[QCOM_RPM_USB_OTG_SWITCH] =		अणु 210, 34, 32, 1 पूर्ण,
	[QCOM_RPM_HDMI_SWITCH] =		अणु 211, 35, 33, 1 पूर्ण,
	[QCOM_RPM_DDR_DMM] =			अणु 212, 36, 34, 2 पूर्ण,
	[QCOM_RPM_VDDMIN_GPIO] =		अणु 215, 40, 39, 1 पूर्ण,
	[QCOM_RPM_SMB208_S1a] =			अणु 216, 41, 90, 2 पूर्ण,
	[QCOM_RPM_SMB208_S1b] =			अणु 218, 43, 91, 2 पूर्ण,
	[QCOM_RPM_SMB208_S2a] =			अणु 220, 45, 92, 2 पूर्ण,
	[QCOM_RPM_SMB208_S2b] =			अणु 222, 47, 93, 2 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_data ipq806x_ढाँचा = अणु
	.version = 3,
	.resource_table = ipq806x_rpm_resource_table,
	.n_resources = ARRAY_SIZE(ipq806x_rpm_resource_table),
	.req_ctx_off = 3,
	.req_sel_off = 11,
	.ack_ctx_off = 15,
	.ack_sel_off = 23,
	.req_sel_size = 4,
	.ack_sel_size = 7,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_resource mdm9615_rpm_resource_table[] = अणु
	[QCOM_RPM_CXO_CLK] =			अणु 25, 9, 5, 1 पूर्ण,
	[QCOM_RPM_SYS_FABRIC_CLK] =		अणु 26, 10, 9, 1 पूर्ण,
	[QCOM_RPM_DAYTONA_FABRIC_CLK] =		अणु 27, 11, 11, 1 पूर्ण,
	[QCOM_RPM_SFPB_CLK] =			अणु 28, 12, 12, 1 पूर्ण,
	[QCOM_RPM_CFPB_CLK] =			अणु 29, 13, 13, 1 पूर्ण,
	[QCOM_RPM_EBI1_CLK] =			अणु 30, 14, 16, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_HALT] =		अणु 31, 15, 22, 2 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_MODE] =		अणु 33, 16, 23, 3 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_IOCTL] =		अणु 36, 17, 24, 1 पूर्ण,
	[QCOM_RPM_APPS_FABRIC_ARB] =		अणु 37, 18, 25, 27 पूर्ण,
	[QCOM_RPM_PM8018_SMPS1] =		अणु 64, 19, 30, 2 पूर्ण,
	[QCOM_RPM_PM8018_SMPS2] =		अणु 66, 21, 31, 2 पूर्ण,
	[QCOM_RPM_PM8018_SMPS3] =		अणु 68, 23, 32, 2 पूर्ण,
	[QCOM_RPM_PM8018_SMPS4] =		अणु 70, 25, 33, 2 पूर्ण,
	[QCOM_RPM_PM8018_SMPS5] =		अणु 72, 27, 34, 2 पूर्ण,
	[QCOM_RPM_PM8018_LDO1] =		अणु 74, 29, 35, 2 पूर्ण,
	[QCOM_RPM_PM8018_LDO2] =		अणु 76, 31, 36, 2 पूर्ण,
	[QCOM_RPM_PM8018_LDO3] =		अणु 78, 33, 37, 2 पूर्ण,
	[QCOM_RPM_PM8018_LDO4] =		अणु 80, 35, 38, 2 पूर्ण,
	[QCOM_RPM_PM8018_LDO5] =		अणु 82, 37, 39, 2 पूर्ण,
	[QCOM_RPM_PM8018_LDO6] =		अणु 84, 39, 40, 2 पूर्ण,
	[QCOM_RPM_PM8018_LDO7] =		अणु 86, 41, 41, 2 पूर्ण,
	[QCOM_RPM_PM8018_LDO8] =		अणु 88, 43, 42, 2 पूर्ण,
	[QCOM_RPM_PM8018_LDO9] =		अणु 90, 45, 43, 2 पूर्ण,
	[QCOM_RPM_PM8018_LDO10] =		अणु 92, 47, 44, 2 पूर्ण,
	[QCOM_RPM_PM8018_LDO11] =		अणु 94, 49, 45, 2 पूर्ण,
	[QCOM_RPM_PM8018_LDO12] =		अणु 96, 51, 46, 2 पूर्ण,
	[QCOM_RPM_PM8018_LDO13] =		अणु 98, 53, 47, 2 पूर्ण,
	[QCOM_RPM_PM8018_LDO14] =		अणु 100, 55, 48, 2 पूर्ण,
	[QCOM_RPM_PM8018_LVS1] =		अणु 102, 57, 49, 1 पूर्ण,
	[QCOM_RPM_PM8018_NCP] =			अणु 103, 58, 80, 2 पूर्ण,
	[QCOM_RPM_CXO_BUFFERS] =		अणु 105, 60, 81, 1 पूर्ण,
	[QCOM_RPM_USB_OTG_SWITCH] =		अणु 106, 61, 82, 1 पूर्ण,
	[QCOM_RPM_HDMI_SWITCH] =		अणु 107, 62, 83, 1 पूर्ण,
	[QCOM_RPM_VOLTAGE_CORNER] =		अणु 109, 64, 87, 1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा qcom_rpm_data mdm9615_ढाँचा = अणु
	.version = 3,
	.resource_table = mdm9615_rpm_resource_table,
	.n_resources = ARRAY_SIZE(mdm9615_rpm_resource_table),
	.req_ctx_off = 3,
	.req_sel_off = 11,
	.ack_ctx_off = 15,
	.ack_sel_off = 23,
	.req_sel_size = 4,
	.ack_sel_size = 7,
पूर्ण;

अटल स्थिर काष्ठा of_device_id qcom_rpm_of_match[] = अणु
	अणु .compatible = "qcom,rpm-apq8064", .data = &apq8064_ढाँचा पूर्ण,
	अणु .compatible = "qcom,rpm-msm8660", .data = &msm8660_ढाँचा पूर्ण,
	अणु .compatible = "qcom,rpm-msm8960", .data = &msm8960_ढाँचा पूर्ण,
	अणु .compatible = "qcom,rpm-ipq8064", .data = &ipq806x_ढाँचा पूर्ण,
	अणु .compatible = "qcom,rpm-mdm9615", .data = &mdm9615_ढाँचा पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_rpm_of_match);

पूर्णांक qcom_rpm_ग_लिखो(काष्ठा qcom_rpm *rpm,
		   पूर्णांक state,
		   पूर्णांक resource,
		   u32 *buf, माप_प्रकार count)
अणु
	स्थिर काष्ठा qcom_rpm_resource *res;
	स्थिर काष्ठा qcom_rpm_data *data = rpm->data;
	u32 sel_mask[RPM_MAX_SEL_SIZE] = अणु 0 पूर्ण;
	पूर्णांक left;
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (WARN_ON(resource < 0 || resource >= data->n_resources))
		वापस -EINVAL;

	res = &data->resource_table[resource];
	अगर (WARN_ON(res->size != count))
		वापस -EINVAL;

	mutex_lock(&rpm->lock);

	क्रम (i = 0; i < res->size; i++)
		ग_लिखोl_relaxed(buf[i], RPM_REQ_REG(rpm, res->target_id + i));

	biपंचांगap_set((अचिन्हित दीर्घ *)sel_mask, res->select_id, 1);
	क्रम (i = 0; i < rpm->data->req_sel_size; i++) अणु
		ग_लिखोl_relaxed(sel_mask[i],
			       RPM_CTRL_REG(rpm, rpm->data->req_sel_off + i));
	पूर्ण

	ग_लिखोl_relaxed(BIT(state), RPM_CTRL_REG(rpm, rpm->data->req_ctx_off));

	reinit_completion(&rpm->ack);
	regmap_ग_लिखो(rpm->ipc_regmap, rpm->ipc_offset, BIT(rpm->ipc_bit));

	left = रुको_क्रम_completion_समयout(&rpm->ack, RPM_REQUEST_TIMEOUT);
	अगर (!left)
		ret = -ETIMEDOUT;
	अन्यथा अगर (rpm->ack_status & RPM_REJECTED)
		ret = -EIO;

	mutex_unlock(&rpm->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(qcom_rpm_ग_लिखो);

अटल irqवापस_t qcom_rpm_ack_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा qcom_rpm *rpm = dev;
	u32 ack;
	पूर्णांक i;

	ack = पढ़ोl_relaxed(RPM_CTRL_REG(rpm, rpm->data->ack_ctx_off));
	क्रम (i = 0; i < rpm->data->ack_sel_size; i++)
		ग_लिखोl_relaxed(0,
			RPM_CTRL_REG(rpm, rpm->data->ack_sel_off + i));
	ग_लिखोl(0, RPM_CTRL_REG(rpm, rpm->data->ack_ctx_off));

	अगर (ack & RPM_NOTIFICATION) अणु
		dev_warn(rpm->dev, "ignoring notification!\n");
	पूर्ण अन्यथा अणु
		rpm->ack_status = ack;
		complete(&rpm->ack);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t qcom_rpm_err_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा qcom_rpm *rpm = dev;

	regmap_ग_लिखो(rpm->ipc_regmap, rpm->ipc_offset, BIT(rpm->ipc_bit));
	dev_err(rpm->dev, "RPM triggered fatal error\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t qcom_rpm_wakeup_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qcom_rpm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *syscon_np;
	काष्ठा resource *res;
	काष्ठा qcom_rpm *rpm;
	u32 fw_version[3];
	पूर्णांक irq_wakeup;
	पूर्णांक irq_ack;
	पूर्णांक irq_err;
	पूर्णांक ret;

	rpm = devm_kzalloc(&pdev->dev, माप(*rpm), GFP_KERNEL);
	अगर (!rpm)
		वापस -ENOMEM;

	rpm->dev = &pdev->dev;
	mutex_init(&rpm->lock);
	init_completion(&rpm->ack);

	/* Enable message RAM घड़ी */
	rpm->ramclk = devm_clk_get(&pdev->dev, "ram");
	अगर (IS_ERR(rpm->ramclk)) अणु
		ret = PTR_ERR(rpm->ramclk);
		अगर (ret == -EPROBE_DEFER)
			वापस ret;
		/*
		 * Fall through in all other हालs, as the घड़ी is
		 * optional. (Does not exist on all platक्रमms.)
		 */
		rpm->ramclk = शून्य;
	पूर्ण
	clk_prepare_enable(rpm->ramclk); /* Accepts शून्य */

	irq_ack = platक्रमm_get_irq_byname(pdev, "ack");
	अगर (irq_ack < 0)
		वापस irq_ack;

	irq_err = platक्रमm_get_irq_byname(pdev, "err");
	अगर (irq_err < 0)
		वापस irq_err;

	irq_wakeup = platक्रमm_get_irq_byname(pdev, "wakeup");
	अगर (irq_wakeup < 0)
		वापस irq_wakeup;

	match = of_match_device(qcom_rpm_of_match, &pdev->dev);
	अगर (!match)
		वापस -ENODEV;
	rpm->data = match->data;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	rpm->status_regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(rpm->status_regs))
		वापस PTR_ERR(rpm->status_regs);
	rpm->ctrl_regs = rpm->status_regs + 0x400;
	rpm->req_regs = rpm->status_regs + 0x600;

	syscon_np = of_parse_phandle(pdev->dev.of_node, "qcom,ipc", 0);
	अगर (!syscon_np) अणु
		dev_err(&pdev->dev, "no qcom,ipc node\n");
		वापस -ENODEV;
	पूर्ण

	rpm->ipc_regmap = syscon_node_to_regmap(syscon_np);
	of_node_put(syscon_np);
	अगर (IS_ERR(rpm->ipc_regmap))
		वापस PTR_ERR(rpm->ipc_regmap);

	ret = of_property_पढ़ो_u32_index(pdev->dev.of_node, "qcom,ipc", 1,
					 &rpm->ipc_offset);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "no offset in qcom,ipc\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32_index(pdev->dev.of_node, "qcom,ipc", 2,
					 &rpm->ipc_bit);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "no bit in qcom,ipc\n");
		वापस -EINVAL;
	पूर्ण

	dev_set_drvdata(&pdev->dev, rpm);

	fw_version[0] = पढ़ोl(RPM_STATUS_REG(rpm, 0));
	fw_version[1] = पढ़ोl(RPM_STATUS_REG(rpm, 1));
	fw_version[2] = पढ़ोl(RPM_STATUS_REG(rpm, 2));
	अगर (fw_version[0] != rpm->data->version) अणु
		dev_err(&pdev->dev,
			"RPM version %u.%u.%u incompatible with driver version %u",
			fw_version[0],
			fw_version[1],
			fw_version[2],
			rpm->data->version);
		वापस -EFAULT;
	पूर्ण

	ग_लिखोl(fw_version[0], RPM_CTRL_REG(rpm, 0));
	ग_लिखोl(fw_version[1], RPM_CTRL_REG(rpm, 1));
	ग_लिखोl(fw_version[2], RPM_CTRL_REG(rpm, 2));

	dev_info(&pdev->dev, "RPM firmware %u.%u.%u\n", fw_version[0],
							fw_version[1],
							fw_version[2]);

	ret = devm_request_irq(&pdev->dev,
			       irq_ack,
			       qcom_rpm_ack_पूर्णांकerrupt,
			       IRQF_TRIGGER_RISING,
			       "qcom_rpm_ack",
			       rpm);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request ack interrupt\n");
		वापस ret;
	पूर्ण

	ret = irq_set_irq_wake(irq_ack, 1);
	अगर (ret)
		dev_warn(&pdev->dev, "failed to mark ack irq as wakeup\n");

	ret = devm_request_irq(&pdev->dev,
			       irq_err,
			       qcom_rpm_err_पूर्णांकerrupt,
			       IRQF_TRIGGER_RISING,
			       "qcom_rpm_err",
			       rpm);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request err interrupt\n");
		वापस ret;
	पूर्ण

	ret = devm_request_irq(&pdev->dev,
			       irq_wakeup,
			       qcom_rpm_wakeup_पूर्णांकerrupt,
			       IRQF_TRIGGER_RISING,
			       "qcom_rpm_wakeup",
			       rpm);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request wakeup interrupt\n");
		वापस ret;
	पूर्ण

	ret = irq_set_irq_wake(irq_wakeup, 1);
	अगर (ret)
		dev_warn(&pdev->dev, "failed to mark wakeup irq as wakeup\n");

	वापस of_platक्रमm_populate(pdev->dev.of_node, शून्य, शून्य, &pdev->dev);
पूर्ण

अटल पूर्णांक qcom_rpm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_rpm *rpm = dev_get_drvdata(&pdev->dev);

	of_platक्रमm_depopulate(&pdev->dev);
	clk_disable_unprepare(rpm->ramclk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver qcom_rpm_driver = अणु
	.probe = qcom_rpm_probe,
	.हटाओ = qcom_rpm_हटाओ,
	.driver  = अणु
		.name  = "qcom_rpm",
		.of_match_table = qcom_rpm_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init qcom_rpm_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&qcom_rpm_driver);
पूर्ण
arch_initcall(qcom_rpm_init);

अटल व्योम __निकास qcom_rpm_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&qcom_rpm_driver);
पूर्ण
module_निकास(qcom_rpm_निकास)

MODULE_DESCRIPTION("Qualcomm Resource Power Manager driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Bjorn Andersson <bjorn.andersson@sonymobile.com>");
