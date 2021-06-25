<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**************************************************************************************************
 * Procedure:    Init boot code/firmware code/data session
 *
 * Description: This routine will initialize firmware. If any error occurs during the initialization
 *		process, the routine shall terminate immediately and वापस fail.
 *		NIC driver should call NdisOpenFile only from MiniportInitialize.
 *
 * Arguments:   The poपूर्णांकer of the adapter

 * Returns:
 *        NDIS_STATUS_FAILURE - the following initialization process should be terminated
 *        NDIS_STATUS_SUCCESS - अगर firmware initialization process success
 **************************************************************************************************/

#समावेश "r8192U.h"
#समावेश "r8192U_hw.h"
#समावेश "r819xU_firmware_img.h"
#समावेश "r819xU_firmware.h"
#समावेश <linux/firmware.h>

अटल व्योम firmware_init_param(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv	*priv = ieee80211_priv(dev);
	rt_firmware		*pfirmware = priv->pFirmware;

	pfirmware->cmdpacket_frag_threshold = GET_COMMAND_PACKET_FRAG_THRESHOLD(MAX_TRANSMIT_BUFFER_SIZE);
पूर्ण

/*
 * segment the img and use the ptr and length to remember info on each segment
 *
 */
अटल bool fw_करोwnload_code(काष्ठा net_device *dev, u8 *code_भव_address,
			     u32 buffer_len)
अणु
	काष्ठा r8192_priv   *priv = ieee80211_priv(dev);
	bool		    rt_status = true;
	u16		    frag_threshold;
	u16		    frag_length, frag_offset = 0;
	पूर्णांक		    i;

	rt_firmware	    *pfirmware = priv->pFirmware;
	काष्ठा sk_buff	    *skb;
	अचिन्हित अक्षर	    *seg_ptr;
	काष्ठा cb_desc		    *tcb_desc;
	u8                  bLastIniPkt;
	u8		    index;

	firmware_init_param(dev);
	/* Fragmentation might be required */
	frag_threshold = pfirmware->cmdpacket_frag_threshold;
	करो अणु
		अगर ((buffer_len - frag_offset) > frag_threshold) अणु
			frag_length = frag_threshold;
			bLastIniPkt = 0;
		पूर्ण अन्यथा अणु
			frag_length = buffer_len - frag_offset;
			bLastIniPkt = 1;
		पूर्ण

		/* Allocate skb buffer to contain firmware info and tx descriptor info
		 * add 4 to aव्योम packet appending overflow.
		 */
		skb  = dev_alloc_skb(USB_HWDESC_HEADER_LEN + frag_length + 4);
		अगर (!skb)
			वापस false;
		स_नकल((अचिन्हित अक्षर *)(skb->cb), &dev, माप(dev));
		tcb_desc = (काष्ठा cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
		tcb_desc->queue_index = TXCMD_QUEUE;
		tcb_desc->bCmdOrInit = DESC_PACKET_TYPE_INIT;
		tcb_desc->bLastIniPkt = bLastIniPkt;

		skb_reserve(skb, USB_HWDESC_HEADER_LEN);
		seg_ptr = skb->data;
		/*
		 * Transक्रमm from little endian to big endian
		 * and pending  zero
		 */
		क्रम (i = 0; i < frag_length; i += 4) अणु
			*seg_ptr++ = ((i+0) < frag_length)?code_भव_address[i+3] : 0;
			*seg_ptr++ = ((i+1) < frag_length)?code_भव_address[i+2] : 0;
			*seg_ptr++ = ((i+2) < frag_length)?code_भव_address[i+1] : 0;
			*seg_ptr++ = ((i+3) < frag_length)?code_भव_address[i+0] : 0;
		पूर्ण
		tcb_desc->txbuf_size = (u16)i;
		skb_put(skb, i);

		index = tcb_desc->queue_index;
		अगर (!priv->ieee80211->check_nic_enough_desc(dev, index) ||
		       (!skb_queue_empty(&priv->ieee80211->skb_रुकोQ[index])) ||
		       (priv->ieee80211->queue_stop)) अणु
			RT_TRACE(COMP_FIRMWARE, "=====================================================> tx full!\n");
			skb_queue_tail(&priv->ieee80211->skb_रुकोQ[tcb_desc->queue_index], skb);
		पूर्ण अन्यथा अणु
			priv->ieee80211->sofपंचांगac_hard_start_xmit(skb, dev);
		पूर्ण

		code_भव_address += frag_length;
		frag_offset += frag_length;

	पूर्ण जबतक (frag_offset < buffer_len);

	वापस rt_status;
पूर्ण

/*
 * Procedure:	Check whether मुख्य code is करोwnload OK. If OK, turn on CPU
 *
 * Description:	CPU रेजिस्टर locates in dअगरferent page against general रेजिस्टर.
 *	    Switch to CPU रेजिस्टर in the begin and चयन back beक्रमe वापस
 *
 *
 * Arguments:   The poपूर्णांकer of the adapter
 *
 * Returns:
 *        NDIS_STATUS_FAILURE - the following initialization process should
 *				be terminated
 *        NDIS_STATUS_SUCCESS - अगर firmware initialization process success
 */
अटल bool CPUcheck_मुख्यcodeok_turnonCPU(काष्ठा net_device *dev)
अणु
	bool		rt_status = true;
	पूर्णांक		check_अ_दोodeOK_समय = 200000, check_bootOk_समय = 200000;
	u32		CPU_status = 0;

	/* Check whether put code OK */
	करो अणु
		पढ़ो_nic_dword(dev, CPU_GEN, &CPU_status);

		अगर (CPU_status&CPU_GEN_PUT_CODE_OK)
			अवरोध;

	पूर्ण जबतक (check_अ_दोodeOK_समय--);

	अगर (!(CPU_status&CPU_GEN_PUT_CODE_OK)) अणु
		RT_TRACE(COMP_ERR, "Download Firmware: Put code fail!\n");
		जाओ CPUCheckMainCodeOKAndTurnOnCPU_Fail;
	पूर्ण अन्यथा अणु
		RT_TRACE(COMP_FIRMWARE, "Download Firmware: Put code ok!\n");
	पूर्ण

	/* Turn On CPU */
	पढ़ो_nic_dword(dev, CPU_GEN, &CPU_status);
	ग_लिखो_nic_byte(dev, CPU_GEN,
		       (u8)((CPU_status | CPU_GEN_PWR_STB_CPU) & 0xff));
	mdelay(1000);

	/* Check whether CPU boot OK */
	करो अणु
		पढ़ो_nic_dword(dev, CPU_GEN, &CPU_status);

		अगर (CPU_status&CPU_GEN_BOOT_RDY)
			अवरोध;
	पूर्ण जबतक (check_bootOk_समय--);

	अगर (!(CPU_status&CPU_GEN_BOOT_RDY))
		जाओ CPUCheckMainCodeOKAndTurnOnCPU_Fail;
	अन्यथा
		RT_TRACE(COMP_FIRMWARE, "Download Firmware: Boot ready!\n");

	वापस rt_status;

CPUCheckMainCodeOKAndTurnOnCPU_Fail:
	RT_TRACE(COMP_ERR, "ERR in %s()\n", __func__);
	rt_status = false;
	वापस rt_status;
पूर्ण

अटल bool CPUcheck_firmware_पढ़ोy(काष्ठा net_device *dev)
अणु
	bool		rt_status = true;
	पूर्णांक		check_समय = 200000;
	u32		CPU_status = 0;

	/* Check Firmware Ready */
	करो अणु
		पढ़ो_nic_dword(dev, CPU_GEN, &CPU_status);

		अगर (CPU_status&CPU_GEN_FIRM_RDY)
			अवरोध;

	पूर्ण जबतक (check_समय--);

	अगर (!(CPU_status&CPU_GEN_FIRM_RDY))
		जाओ CPUCheckFirmwareReady_Fail;
	अन्यथा
		RT_TRACE(COMP_FIRMWARE, "Download Firmware: Firmware ready!\n");

	वापस rt_status;

CPUCheckFirmwareReady_Fail:
	RT_TRACE(COMP_ERR, "ERR in %s()\n", __func__);
	rt_status = false;
	वापस rt_status;
पूर्ण

bool init_firmware(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv	*priv = ieee80211_priv(dev);
	bool			rt_status = true;

	u32			file_length = 0;
	u8			*mapped_file = शून्य;
	u32			init_step = 0;
	क्रमागत opt_rst_type_e	   rst_opt = OPT_SYSTEM_RESET;
	क्रमागत firmware_init_step_e  starting_state = FW_INIT_STEP0_BOOT;

	rt_firmware		*pfirmware = priv->pFirmware;
	स्थिर काष्ठा firmware	*fw_entry;
	स्थिर अक्षर *fw_name[3] = अणु "RTL8192U/boot.img",
			   "RTL8192U/main.img",
			   "RTL8192U/data.img"पूर्ण;
	पूर्णांक rc;

	RT_TRACE(COMP_FIRMWARE, " PlatformInitFirmware()==>\n");

	अगर (pfirmware->firmware_status == FW_STATUS_0_INIT) अणु
		/* it is called by reset */
		rst_opt = OPT_SYSTEM_RESET;
		starting_state = FW_INIT_STEP0_BOOT;
		/* TODO: प्रणाली reset */

	पूर्ण अन्यथा अगर (pfirmware->firmware_status == FW_STATUS_5_READY) अणु
		/* it is called by Initialize */
		rst_opt = OPT_FIRMWARE_RESET;
		starting_state = FW_INIT_STEP2_DATA;
	पूर्ण अन्यथा अणु
		RT_TRACE(COMP_FIRMWARE, "PlatformInitFirmware: undefined firmware state\n");
	पूर्ण

	/*
	 * Download boot, मुख्य, and data image क्रम System reset.
	 * Download data image क्रम firmware reset
	 */
	क्रम (init_step = starting_state; init_step <= FW_INIT_STEP2_DATA; init_step++) अणु
		/*
		 * Open image file, and map file to continuous memory अगर खोलो file success.
		 * or पढ़ो image file from array. Default load from IMG file
		 */
		अगर (rst_opt == OPT_SYSTEM_RESET) अणु
			rc = request_firmware(&fw_entry, fw_name[init_step], &priv->udev->dev);
			अगर (rc < 0) अणु
				RT_TRACE(COMP_ERR, "request firmware fail!\n");
				जाओ करोwnload_firmware_fail;
			पूर्ण

			अगर (fw_entry->size > माप(pfirmware->firmware_buf)) अणु
				RT_TRACE(COMP_ERR, "img file size exceed the container buffer fail!\n");
				जाओ करोwnload_firmware_fail;
			पूर्ण

			अगर (init_step != FW_INIT_STEP1_MAIN) अणु
				स_नकल(pfirmware->firmware_buf, fw_entry->data, fw_entry->size);
				mapped_file = pfirmware->firmware_buf;
				file_length = fw_entry->size;
			पूर्ण अन्यथा अणु
				स_रखो(pfirmware->firmware_buf, 0, 128);
				स_नकल(&pfirmware->firmware_buf[128], fw_entry->data, fw_entry->size);
				mapped_file = pfirmware->firmware_buf;
				file_length = fw_entry->size + 128;
			पूर्ण
			pfirmware->firmware_buf_size = file_length;
		पूर्ण अन्यथा अगर (rst_opt == OPT_FIRMWARE_RESET) अणु
			/* we only need to करोwnload data.img here */
			mapped_file = pfirmware->firmware_buf;
			file_length = pfirmware->firmware_buf_size;
		पूर्ण

		/* Download image file */
		/* The firmware करोwnload process is just as following,
		 * 1. that is each packet will be segmented and inserted to the रुको queue.
		 * 2. each packet segment will be put in the skb_buff packet.
		 * 3. each skb_buff packet data content will alपढ़ोy include the firmware info
		 *   and Tx descriptor info
		 */
		rt_status = fw_करोwnload_code(dev, mapped_file, file_length);
		अगर (rst_opt == OPT_SYSTEM_RESET)
			release_firmware(fw_entry);

		अगर (!rt_status)
			जाओ करोwnload_firmware_fail;

		चयन (init_step) अणु
		हाल FW_INIT_STEP0_BOOT:
			/* Download boot
			 * initialize command descriptor.
			 * will set polling bit when firmware code is also configured
			 */
			pfirmware->firmware_status = FW_STATUS_1_MOVE_BOOT_CODE;
			/* mdelay(1000); */
			/*
			 * To initialize IMEM, CPU move code  from 0x80000080,
			 * hence, we send 0x80 byte packet
			 */
			अवरोध;

		हाल FW_INIT_STEP1_MAIN:
			/* Download firmware code. Wait until Boot Ready and Turn on CPU */
			pfirmware->firmware_status = FW_STATUS_2_MOVE_MAIN_CODE;

			/* Check Put Code OK and Turn On CPU */
			rt_status = CPUcheck_मुख्यcodeok_turnonCPU(dev);
			अगर (!rt_status) अणु
				RT_TRACE(COMP_ERR, "CPUcheck_maincodeok_turnonCPU fail!\n");
				जाओ करोwnload_firmware_fail;
			पूर्ण

			pfirmware->firmware_status = FW_STATUS_3_TURNON_CPU;
			अवरोध;

		हाल FW_INIT_STEP2_DATA:
			/* करोwnload initial data code */
			pfirmware->firmware_status = FW_STATUS_4_MOVE_DATA_CODE;
			mdelay(1);

			rt_status = CPUcheck_firmware_पढ़ोy(dev);
			अगर (!rt_status) अणु
				RT_TRACE(COMP_ERR, "CPUcheck_firmware_ready fail(%d)!\n", rt_status);
				जाओ करोwnload_firmware_fail;
			पूर्ण

			/* रुको until data code is initialized पढ़ोy.*/
			pfirmware->firmware_status = FW_STATUS_5_READY;
			अवरोध;
		पूर्ण
	पूर्ण

	RT_TRACE(COMP_FIRMWARE, "Firmware Download Success\n");
	वापस rt_status;

करोwnload_firmware_fail:
	RT_TRACE(COMP_ERR, "ERR in %s()\n", __func__);
	rt_status = false;
	वापस rt_status;
पूर्ण

MODULE_FIRMWARE("RTL8192U/boot.img");
MODULE_FIRMWARE("RTL8192U/main.img");
MODULE_FIRMWARE("RTL8192U/data.img");
