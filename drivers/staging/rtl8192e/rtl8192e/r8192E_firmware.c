<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश "rtl_core.h"
#समावेश "r8192E_hw.h"
#समावेश "r8192E_hwimg.h"
#समावेश "r8192E_firmware.h"
#समावेश "r8192E_cmdpkt.h"
#समावेश <linux/firmware.h>

अटल bool _rtl92e_रुको_क्रम_fw(काष्ठा net_device *dev, u32 mask, u32 समयout)
अणु
	अचिन्हित दीर्घ deadline = jअगरfies + msecs_to_jअगरfies(समयout);

	जबतक (समय_beक्रमe(jअगरfies, deadline)) अणु
		अगर (rtl92e_पढ़ोl(dev, CPU_GEN) & mask)
			वापस true;
		mdelay(2);
	पूर्ण
	वापस false;
पूर्ण

अटल bool _rtl92e_fw_boot_cpu(काष्ठा net_device *dev)
अणु
	u32		CPU_status = 0;

	अगर (!_rtl92e_रुको_क्रम_fw(dev, CPU_GEN_PUT_CODE_OK, 200)) अणु
		netdev_err(dev, "Firmware download failed.\n");
		वापस false;
	पूर्ण
	netdev_dbg(dev, "Download Firmware: Put code ok!\n");

	CPU_status = rtl92e_पढ़ोl(dev, CPU_GEN);
	rtl92e_ग_लिखोb(dev, CPU_GEN,
		      (u8)((CPU_status|CPU_GEN_PWR_STB_CPU)&0xff));
	mdelay(1);

	अगर (!_rtl92e_रुको_क्रम_fw(dev, CPU_GEN_BOOT_RDY, 200)) अणु
		netdev_err(dev, "Firmware boot failed.\n");
		वापस false;
	पूर्ण

	netdev_dbg(dev, "Download Firmware: Boot ready!\n");

	वापस true;
पूर्ण

अटल bool _rtl92e_fw_check_पढ़ोy(काष्ठा net_device *dev,
				   u8 load_fw_status)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rt_firmware *pfirmware = priv->pFirmware;
	bool rt_status  = true;

	चयन (load_fw_status) अणु
	हाल FW_INIT_STEP0_BOOT:
		pfirmware->status = FW_STATUS_1_MOVE_BOOT_CODE;
		अवरोध;

	हाल FW_INIT_STEP1_MAIN:
		pfirmware->status = FW_STATUS_2_MOVE_MAIN_CODE;

		rt_status = _rtl92e_fw_boot_cpu(dev);
		अगर (rt_status)
			pfirmware->status = FW_STATUS_3_TURNON_CPU;
		अन्यथा
			netdev_dbg(dev, "_rtl92e_fw_boot_cpu fail!\n");

		अवरोध;

	हाल FW_INIT_STEP2_DATA:
		pfirmware->status = FW_STATUS_4_MOVE_DATA_CODE;
		mdelay(1);

		rt_status = _rtl92e_रुको_क्रम_fw(dev, CPU_GEN_FIRM_RDY, 20);
		अगर (rt_status)
			pfirmware->status = FW_STATUS_5_READY;
		अन्यथा
			RT_TRACE(COMP_FIRMWARE,
				 "_rtl92e_is_fw_ready fail(%d)!\n",
				 rt_status);
		अवरोध;
	शेष:
		rt_status = false;
		netdev_dbg(dev, "Unknown firmware status");
		अवरोध;
	पूर्ण

	वापस rt_status;
पूर्ण

अटल bool _rtl92e_fw_prepare(काष्ठा net_device *dev, काष्ठा rt_fw_blob *blob,
			       स्थिर अक्षर *name, u8 padding)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक rc, i;
	bool ret = true;

	rc = request_firmware(&fw, name, &dev->dev);
	अगर (rc < 0)
		वापस false;

	अगर (round_up(fw->size, 4) > MAX_FW_SIZE - padding) अणु
		netdev_err(dev, "Firmware image %s too big for the device.\n",
			   name);
		ret = false;
		जाओ out;
	पूर्ण

	अगर (padding)
		स_रखो(blob->data, 0, padding);
	अगर (fw->size % 4)
		स_रखो(blob->data + padding + fw->size, 0, 4);
	स_नकल(blob->data + padding, fw->data, fw->size);

	blob->size = round_up(fw->size, 4) + padding;

	/* Swap endian - firmware is packaged in invalid endiannes*/
	क्रम (i = padding; i < blob->size; i += 4) अणु
		u32 *data = (u32 *)(blob->data + i);
		*data = swab32p(data);
	पूर्ण
out:
	release_firmware(fw);
	वापस ret;
पूर्ण

bool rtl92e_init_fw(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	bool			rt_status = true;

	u32	file_length = 0;
	u8	*mapped_file = शून्य;
	u8	i = 0;
	क्रमागत opt_rst_type rst_opt = OPT_SYSTEM_RESET;
	क्रमागत firmware_init_step starting_state = FW_INIT_STEP0_BOOT;

	काष्ठा rt_firmware *pfirmware = priv->pFirmware;

	netdev_dbg(dev, " PlatformInitFirmware()==>\n");

	अगर (pfirmware->status == FW_STATUS_0_INIT) अणु
		rst_opt = OPT_SYSTEM_RESET;
		starting_state = FW_INIT_STEP0_BOOT;

	पूर्ण अन्यथा अगर (pfirmware->status == FW_STATUS_5_READY) अणु
		rst_opt = OPT_FIRMWARE_RESET;
		starting_state = FW_INIT_STEP2_DATA;
	पूर्ण अन्यथा अणु
		RT_TRACE(COMP_FIRMWARE,
			 "PlatformInitFirmware: undefined firmware state\n");
	पूर्ण

	क्रम (i = starting_state; i <= FW_INIT_STEP2_DATA; i++) अणु
		अगर (rst_opt == OPT_SYSTEM_RESET) अणु
			अगर (pfirmware->blobs[i].size == 0) अणु
				स्थिर अक्षर *fw_name[3] = अणु
					RTL8192E_BOOT_IMG_FW,
					RTL8192E_MAIN_IMG_FW,
					RTL8192E_DATA_IMG_FW
				पूर्ण;
				पूर्णांक pad = 0;

				अगर (i == FW_INIT_STEP1_MAIN)
					pad = 128;

				अगर (!_rtl92e_fw_prepare(dev,
							&pfirmware->blobs[i],
							fw_name[i],
							pad))
					जाओ करोwnload_firmware_fail;
			पूर्ण
		पूर्ण

		mapped_file = pfirmware->blobs[i].data;
		file_length = pfirmware->blobs[i].size;

		rt_status = rtl92e_send_cmd_pkt(dev, DESC_PACKET_TYPE_INIT,
						mapped_file, file_length);
		अगर (!rt_status)
			जाओ करोwnload_firmware_fail;

		अगर (!_rtl92e_fw_check_पढ़ोy(dev, i))
			जाओ करोwnload_firmware_fail;
	पूर्ण

	netdev_dbg(dev, "Firmware Download Success\n");
	वापस rt_status;

करोwnload_firmware_fail:
	netdev_err(dev, "%s: Failed to initialize firmware.\n", __func__);
	वापस false;
पूर्ण
