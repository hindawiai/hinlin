<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/******************************************************************************
 *  cxacru.c  -  driver क्रम USB ADSL modems based on
 *               Conexant AccessRunner chipset
 *
 *  Copyright (C) 2004 David Woodhouse, Duncan Sands, Roman Kagan
 *  Copyright (C) 2005 Duncan Sands, Roman Kagan (rkagan % mail ! ru)
 *  Copyright (C) 2007 Simon Arlott
 *  Copyright (C) 2009 Simon Arlott
 ******************************************************************************/

/*
 *  Credit is due क्रम Josep Comas, who created the original patch to speedtch.c
 *  to support the dअगरferent padding used by the AccessRunner (now generalized
 *  पूर्णांकo usbaपंचांग), and the userspace firmware loading utility.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "usbatm.h"

#घोषणा DRIVER_AUTHOR	"Roman Kagan, David Woodhouse, Duncan Sands, Simon Arlott"
#घोषणा DRIVER_DESC	"Conexant AccessRunner ADSL USB modem driver"

अटल स्थिर अक्षर cxacru_driver_name[] = "cxacru";

#घोषणा CXACRU_EP_CMD		0x01	/* Bulk/पूर्णांकerrupt in/out */
#घोषणा CXACRU_EP_DATA		0x02	/* Bulk in/out */

#घोषणा CMD_PACKET_SIZE		64	/* Should be maxpacket(ep)? */
#घोषणा CMD_MAX_CONFIG		((CMD_PACKET_SIZE / 4 - 1) / 2)

/* Addresses */
#घोषणा PLLFCLK_ADDR	0x00350068
#घोषणा PLLBCLK_ADDR	0x0035006c
#घोषणा SDRAMEN_ADDR	0x00350010
#घोषणा FW_ADDR		0x00801000
#घोषणा BR_ADDR		0x00180600
#घोषणा SIG_ADDR	0x00180500
#घोषणा BR_STACK_ADDR	0x00187f10

/* Values */
#घोषणा SDRAM_ENA	0x1

#घोषणा CMD_TIMEOUT	2000	/* msecs */
#घोषणा POLL_INTERVAL	1	/* secs */

/* commands क्रम पूर्णांकeraction with the modem through the control channel beक्रमe
 * firmware is loaded  */
क्रमागत cxacru_fw_request अणु
	FW_CMD_ERR,
	FW_GET_VER,
	FW_READ_MEM,
	FW_WRITE_MEM,
	FW_RMW_MEM,
	FW_CHECKSUM_MEM,
	FW_GOTO_MEM,
पूर्ण;

/* commands क्रम पूर्णांकeraction with the modem through the control channel once
 * firmware is loaded  */
क्रमागत cxacru_cm_request अणु
	CM_REQUEST_UNDEFINED = 0x80,
	CM_REQUEST_TEST,
	CM_REQUEST_CHIP_GET_MAC_ADDRESS,
	CM_REQUEST_CHIP_GET_DP_VERSIONS,
	CM_REQUEST_CHIP_ADSL_LINE_START,
	CM_REQUEST_CHIP_ADSL_LINE_STOP,
	CM_REQUEST_CHIP_ADSL_LINE_GET_STATUS,
	CM_REQUEST_CHIP_ADSL_LINE_GET_SPEED,
	CM_REQUEST_CARD_INFO_GET,
	CM_REQUEST_CARD_DATA_GET,
	CM_REQUEST_CARD_DATA_SET,
	CM_REQUEST_COMMAND_HW_IO,
	CM_REQUEST_INTERFACE_HW_IO,
	CM_REQUEST_CARD_SERIAL_DATA_PATH_GET,
	CM_REQUEST_CARD_SERIAL_DATA_PATH_SET,
	CM_REQUEST_CARD_CONTROLLER_VERSION_GET,
	CM_REQUEST_CARD_GET_STATUS,
	CM_REQUEST_CARD_GET_MAC_ADDRESS,
	CM_REQUEST_CARD_GET_DATA_LINK_STATUS,
	CM_REQUEST_MAX,
पूर्ण;

/* commands क्रम पूर्णांकeraction with the flash memory
 *
 * पढ़ो:  response is the contents of the first 60 bytes of flash memory
 * ग_लिखो: request contains the 60 bytes of data to ग_लिखो to flash memory
 *        response is the contents of the first 60 bytes of flash memory
 *
 * layout: PP PP VV VV  MM MM MM MM  MM MM ?? ??  SS SS SS SS  SS SS SS SS
 *         SS SS SS SS  SS SS SS SS  00 00 00 00  00 00 00 00  00 00 00 00
 *         00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00
 *
 *   P: le16  USB Product ID
 *   V: le16  USB Venकरोr ID
 *   M: be48  MAC Address
 *   S: le16  ASCII Serial Number
 */
क्रमागत cxacru_cm_flash अणु
	CM_FLASH_READ = 0xa1,
	CM_FLASH_WRITE = 0xa2
पूर्ण;

/* reply codes to the commands above */
क्रमागत cxacru_cm_status अणु
	CM_STATUS_UNDEFINED,
	CM_STATUS_SUCCESS,
	CM_STATUS_ERROR,
	CM_STATUS_UNSUPPORTED,
	CM_STATUS_UNIMPLEMENTED,
	CM_STATUS_PARAMETER_ERROR,
	CM_STATUS_DBG_LOOPBACK,
	CM_STATUS_MAX,
पूर्ण;

/* indices पूर्णांकo CARD_INFO_GET वापस array */
क्रमागत cxacru_info_idx अणु
	CXINF_DOWNSTREAM_RATE,
	CXINF_UPSTREAM_RATE,
	CXINF_LINK_STATUS,
	CXINF_LINE_STATUS,
	CXINF_MAC_ADDRESS_HIGH,
	CXINF_MAC_ADDRESS_LOW,
	CXINF_UPSTREAM_SNR_MARGIN,
	CXINF_DOWNSTREAM_SNR_MARGIN,
	CXINF_UPSTREAM_ATTENUATION,
	CXINF_DOWNSTREAM_ATTENUATION,
	CXINF_TRANSMITTER_POWER,
	CXINF_UPSTREAM_BITS_PER_FRAME,
	CXINF_DOWNSTREAM_BITS_PER_FRAME,
	CXINF_STARTUP_ATTEMPTS,
	CXINF_UPSTREAM_CRC_ERRORS,
	CXINF_DOWNSTREAM_CRC_ERRORS,
	CXINF_UPSTREAM_FEC_ERRORS,
	CXINF_DOWNSTREAM_FEC_ERRORS,
	CXINF_UPSTREAM_HEC_ERRORS,
	CXINF_DOWNSTREAM_HEC_ERRORS,
	CXINF_LINE_STARTABLE,
	CXINF_MODULATION,
	CXINF_ADSL_HEADEND,
	CXINF_ADSL_HEADEND_ENVIRONMENT,
	CXINF_CONTROLLER_VERSION,
	/* dunno what the missing two mean */
	CXINF_MAX = 0x1c,
पूर्ण;

क्रमागत cxacru_poll_state अणु
	CXPOLL_STOPPING,
	CXPOLL_STOPPED,
	CXPOLL_POLLING,
	CXPOLL_SHUTDOWN
पूर्ण;

काष्ठा cxacru_modem_type अणु
	u32 pll_f_clk;
	u32 pll_b_clk;
	पूर्णांक boot_rom_patch;
पूर्ण;

काष्ठा cxacru_data अणु
	काष्ठा usbaपंचांग_data *usbaपंचांग;

	स्थिर काष्ठा cxacru_modem_type *modem_type;

	पूर्णांक line_status;
	काष्ठा mutex adsl_state_serialize;
	पूर्णांक adsl_status;
	काष्ठा delayed_work poll_work;
	u32 card_info[CXINF_MAX];
	काष्ठा mutex poll_state_serialize;
	क्रमागत cxacru_poll_state poll_state;

	/* contol handles */
	काष्ठा mutex cm_serialize;
	u8 *rcv_buf;
	u8 *snd_buf;
	काष्ठा urb *rcv_urb;
	काष्ठा urb *snd_urb;
	काष्ठा completion rcv_करोne;
	काष्ठा completion snd_करोne;
पूर्ण;

अटल पूर्णांक cxacru_cm(काष्ठा cxacru_data *instance, क्रमागत cxacru_cm_request cm,
	u8 *wdata, पूर्णांक wsize, u8 *rdata, पूर्णांक rsize);
अटल व्योम cxacru_poll_status(काष्ठा work_काष्ठा *work);

/* Card info exported through sysfs */
#घोषणा CXACRU__ATTR_INIT(_name) \
अटल DEVICE_ATTR_RO(_name)

#घोषणा CXACRU_CMD_INIT(_name) \
अटल DEVICE_ATTR_RW(_name)

#घोषणा CXACRU_SET_INIT(_name) \
अटल DEVICE_ATTR_WO(_name)

#घोषणा CXACRU_ATTR_INIT(_value, _type, _name) \
अटल sमाप_प्रकार _name##_show(काष्ठा device *dev, \
	काष्ठा device_attribute *attr, अक्षर *buf) \
अणु \
	काष्ठा cxacru_data *instance = to_usbaपंचांग_driver_data(\
		to_usb_पूर्णांकerface(dev)); \
\
	अगर (instance == शून्य) \
		वापस -ENODEV; \
\
	वापस cxacru_sysfs_showattr_##_type(instance->card_info[_value], buf); \
पूर्ण \
CXACRU__ATTR_INIT(_name)

#घोषणा CXACRU_ATTR_CREATE(_v, _t, _name) CXACRU_DEVICE_CREATE_खाता(_name)
#घोषणा CXACRU_CMD_CREATE(_name)          CXACRU_DEVICE_CREATE_खाता(_name)
#घोषणा CXACRU_SET_CREATE(_name)          CXACRU_DEVICE_CREATE_खाता(_name)
#घोषणा CXACRU__ATTR_CREATE(_name)        CXACRU_DEVICE_CREATE_खाता(_name)

#घोषणा CXACRU_ATTR_REMOVE(_v, _t, _name) CXACRU_DEVICE_REMOVE_खाता(_name)
#घोषणा CXACRU_CMD_REMOVE(_name)          CXACRU_DEVICE_REMOVE_खाता(_name)
#घोषणा CXACRU_SET_REMOVE(_name)          CXACRU_DEVICE_REMOVE_खाता(_name)
#घोषणा CXACRU__ATTR_REMOVE(_name)        CXACRU_DEVICE_REMOVE_खाता(_name)

अटल sमाप_प्रकार cxacru_sysfs_showattr_u32(u32 value, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", value);
पूर्ण

अटल sमाप_प्रकार cxacru_sysfs_showattr_s8(s8 value, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार cxacru_sysfs_showattr_dB(s16 value, अक्षर *buf)
अणु
	अगर (likely(value >= 0)) अणु
		वापस snम_लिखो(buf, PAGE_SIZE, "%u.%02u\n",
					value / 100, value % 100);
	पूर्ण अन्यथा अणु
		value = -value;
		वापस snम_लिखो(buf, PAGE_SIZE, "-%u.%02u\n",
					value / 100, value % 100);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार cxacru_sysfs_showattr_bool(u32 value, अक्षर *buf)
अणु
	अटल अक्षर *str[] = अणु "no", "yes" पूर्ण;

	अगर (unlikely(value >= ARRAY_SIZE(str)))
		वापस प्र_लिखो(buf, "%u\n", value);
	वापस प्र_लिखो(buf, "%s\n", str[value]);
पूर्ण

अटल sमाप_प्रकार cxacru_sysfs_showattr_LINK(u32 value, अक्षर *buf)
अणु
	अटल अक्षर *str[] = अणु शून्य, "not connected", "connected", "lost" पूर्ण;

	अगर (unlikely(value >= ARRAY_SIZE(str) || str[value] == शून्य))
		वापस प्र_लिखो(buf, "%u\n", value);
	वापस प्र_लिखो(buf, "%s\n", str[value]);
पूर्ण

अटल sमाप_प्रकार cxacru_sysfs_showattr_LINE(u32 value, अक्षर *buf)
अणु
	अटल अक्षर *str[] = अणु "down", "attempting to activate",
		"training", "channel analysis", "exchange", "up",
		"waiting", "initialising"
	पूर्ण;
	अगर (unlikely(value >= ARRAY_SIZE(str)))
		वापस प्र_लिखो(buf, "%u\n", value);
	वापस प्र_लिखो(buf, "%s\n", str[value]);
पूर्ण

अटल sमाप_प्रकार cxacru_sysfs_showattr_MODU(u32 value, अक्षर *buf)
अणु
	अटल अक्षर *str[] = अणु
			"",
			"ANSI T1.413",
			"ITU-T G.992.1 (G.DMT)",
			"ITU-T G.992.2 (G.LITE)"
	पूर्ण;
	अगर (unlikely(value >= ARRAY_SIZE(str)))
		वापस प्र_लिखो(buf, "%u\n", value);
	वापस प्र_लिखो(buf, "%s\n", str[value]);
पूर्ण

/*
 * This could use MAC_ADDRESS_HIGH and MAC_ADDRESS_LOW, but since
 * this data is alपढ़ोy in aपंचांग_dev there's no poपूर्णांक.
 *
 * MAC_ADDRESS_HIGH = 0x????5544
 * MAC_ADDRESS_LOW  = 0x33221100
 * Where 00-55 are bytes 0-5 of the MAC.
 */
अटल sमाप_प्रकार mac_address_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cxacru_data *instance = to_usbaपंचांग_driver_data(
			to_usb_पूर्णांकerface(dev));

	अगर (instance == शून्य || instance->usbaपंचांग->aपंचांग_dev == शून्य)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%pM\n", instance->usbaपंचांग->aपंचांग_dev->esi);
पूर्ण

अटल sमाप_प्रकार adsl_state_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अटल अक्षर *str[] = अणु "running", "stopped" पूर्ण;
	काष्ठा cxacru_data *instance = to_usbaपंचांग_driver_data(
			to_usb_पूर्णांकerface(dev));
	u32 value;

	अगर (instance == शून्य)
		वापस -ENODEV;

	value = instance->card_info[CXINF_LINE_STARTABLE];
	अगर (unlikely(value >= ARRAY_SIZE(str)))
		वापस प्र_लिखो(buf, "%u\n", value);
	वापस प्र_लिखो(buf, "%s\n", str[value]);
पूर्ण

अटल sमाप_प्रकार adsl_state_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cxacru_data *instance = to_usbaपंचांग_driver_data(
			to_usb_पूर्णांकerface(dev));
	पूर्णांक ret;
	पूर्णांक poll = -1;
	अक्षर str_cmd[8];
	पूर्णांक len = म_माप(buf);

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EACCES;

	ret = माला_पूछो(buf, "%7s", str_cmd);
	अगर (ret != 1)
		वापस -EINVAL;
	ret = 0;

	अगर (instance == शून्य)
		वापस -ENODEV;

	अगर (mutex_lock_पूर्णांकerruptible(&instance->adsl_state_serialize))
		वापस -ERESTARTSYS;

	अगर (!म_भेद(str_cmd, "stop") || !म_भेद(str_cmd, "restart")) अणु
		ret = cxacru_cm(instance, CM_REQUEST_CHIP_ADSL_LINE_STOP, शून्य, 0, शून्य, 0);
		अगर (ret < 0) अणु
			aपंचांग_err(instance->usbaपंचांग, "change adsl state:"
				" CHIP_ADSL_LINE_STOP returned %d\n", ret);

			ret = -EIO;
		पूर्ण अन्यथा अणु
			ret = len;
			poll = CXPOLL_STOPPED;
		पूर्ण
	पूर्ण

	/* Line status is only updated every second
	 * and the device appears to only react to
	 * START/STOP every second too. Wait 1.5s to
	 * be sure that restart will have an effect. */
	अगर (!म_भेद(str_cmd, "restart"))
		msleep(1500);

	अगर (!म_भेद(str_cmd, "start") || !म_भेद(str_cmd, "restart")) अणु
		ret = cxacru_cm(instance, CM_REQUEST_CHIP_ADSL_LINE_START, शून्य, 0, शून्य, 0);
		अगर (ret < 0) अणु
			aपंचांग_err(instance->usbaपंचांग, "change adsl state:"
				" CHIP_ADSL_LINE_START returned %d\n", ret);

			ret = -EIO;
		पूर्ण अन्यथा अणु
			ret = len;
			poll = CXPOLL_POLLING;
		पूर्ण
	पूर्ण

	अगर (!म_भेद(str_cmd, "poll")) अणु
		ret = len;
		poll = CXPOLL_POLLING;
	पूर्ण

	अगर (ret == 0) अणु
		ret = -EINVAL;
		poll = -1;
	पूर्ण

	अगर (poll == CXPOLL_POLLING) अणु
		mutex_lock(&instance->poll_state_serialize);
		चयन (instance->poll_state) अणु
		हाल CXPOLL_STOPPED:
			/* start polling */
			instance->poll_state = CXPOLL_POLLING;
			अवरोध;

		हाल CXPOLL_STOPPING:
			/* पात stop request */
			instance->poll_state = CXPOLL_POLLING;
			fallthrough;
		हाल CXPOLL_POLLING:
		हाल CXPOLL_SHUTDOWN:
			/* करोn't start polling */
			poll = -1;
		पूर्ण
		mutex_unlock(&instance->poll_state_serialize);
	पूर्ण अन्यथा अगर (poll == CXPOLL_STOPPED) अणु
		mutex_lock(&instance->poll_state_serialize);
		/* request stop */
		अगर (instance->poll_state == CXPOLL_POLLING)
			instance->poll_state = CXPOLL_STOPPING;
		mutex_unlock(&instance->poll_state_serialize);
	पूर्ण

	mutex_unlock(&instance->adsl_state_serialize);

	अगर (poll == CXPOLL_POLLING)
		cxacru_poll_status(&instance->poll_work.work);

	वापस ret;
पूर्ण

/* CM_REQUEST_CARD_DATA_GET बार out, so no show attribute */

अटल sमाप_प्रकार adsl_config_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cxacru_data *instance = to_usbaपंचांग_driver_data(
			to_usb_पूर्णांकerface(dev));
	पूर्णांक len = म_माप(buf);
	पूर्णांक ret, pos, num;
	__le32 data[CMD_PACKET_SIZE / 4];

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EACCES;

	अगर (instance == शून्य)
		वापस -ENODEV;

	pos = 0;
	num = 0;
	जबतक (pos < len) अणु
		पूर्णांक पंचांगp;
		u32 index;
		u32 value;

		ret = माला_पूछो(buf + pos, "%x=%x%n", &index, &value, &पंचांगp);
		अगर (ret < 2)
			वापस -EINVAL;
		अगर (index > 0x7f)
			वापस -EINVAL;
		अगर (पंचांगp < 0 || पंचांगp > len - pos)
			वापस -EINVAL;
		pos += पंचांगp;

		/* skip trailing newline */
		अगर (buf[pos] == '\n' && pos == len-1)
			pos++;

		data[num * 2 + 1] = cpu_to_le32(index);
		data[num * 2 + 2] = cpu_to_le32(value);
		num++;

		/* send config values when data buffer is full
		 * or no more data
		 */
		अगर (pos >= len || num >= CMD_MAX_CONFIG) अणु
			अक्षर log[CMD_MAX_CONFIG * 12 + 1]; /* %02x=%08x */

			data[0] = cpu_to_le32(num);
			ret = cxacru_cm(instance, CM_REQUEST_CARD_DATA_SET,
				(u8 *) data, 4 + num * 8, शून्य, 0);
			अगर (ret < 0) अणु
				aपंचांग_err(instance->usbaपंचांग,
					"set card data returned %d\n", ret);
				वापस -EIO;
			पूर्ण

			क्रम (पंचांगp = 0; पंचांगp < num; पंचांगp++)
				snम_लिखो(log + पंचांगp*12, 13, " %02x=%08x",
					le32_to_cpu(data[पंचांगp * 2 + 1]),
					le32_to_cpu(data[पंचांगp * 2 + 2]));
			aपंचांग_info(instance->usbaपंचांग, "config%s\n", log);
			num = 0;
		पूर्ण
	पूर्ण

	वापस len;
पूर्ण

/*
 * All device attributes are included in CXACRU_ALL_खाताS
 * so that the same list can be used multiple बार:
 *     INIT   (define the device attributes)
 *     CREATE (create all the device files)
 *     REMOVE (हटाओ all the device files)
 *
 * With the last two being defined as needed in the functions
 * they are used in beक्रमe calling CXACRU_ALL_खाताS()
 */
#घोषणा CXACRU_ALL_खाताS(_action) \
CXACRU_ATTR_##_action(CXINF_DOWNSTREAM_RATE,           u32,  करोwnstream_rate); \
CXACRU_ATTR_##_action(CXINF_UPSTREAM_RATE,             u32,  upstream_rate); \
CXACRU_ATTR_##_action(CXINF_LINK_STATUS,               LINK, link_status); \
CXACRU_ATTR_##_action(CXINF_LINE_STATUS,               LINE, line_status); \
CXACRU__ATTR_##_action(                                      mac_address); \
CXACRU_ATTR_##_action(CXINF_UPSTREAM_SNR_MARGIN,       dB,   upstream_snr_margin); \
CXACRU_ATTR_##_action(CXINF_DOWNSTREAM_SNR_MARGIN,     dB,   करोwnstream_snr_margin); \
CXACRU_ATTR_##_action(CXINF_UPSTREAM_ATTENUATION,      dB,   upstream_attenuation); \
CXACRU_ATTR_##_action(CXINF_DOWNSTREAM_ATTENUATION,    dB,   करोwnstream_attenuation); \
CXACRU_ATTR_##_action(CXINF_TRANSMITTER_POWER,         s8,   transmitter_घातer); \
CXACRU_ATTR_##_action(CXINF_UPSTREAM_BITS_PER_FRAME,   u32,  upstream_bits_per_frame); \
CXACRU_ATTR_##_action(CXINF_DOWNSTREAM_BITS_PER_FRAME, u32,  करोwnstream_bits_per_frame); \
CXACRU_ATTR_##_action(CXINF_STARTUP_ATTEMPTS,          u32,  startup_attempts); \
CXACRU_ATTR_##_action(CXINF_UPSTREAM_CRC_ERRORS,       u32,  upstream_crc_errors); \
CXACRU_ATTR_##_action(CXINF_DOWNSTREAM_CRC_ERRORS,     u32,  करोwnstream_crc_errors); \
CXACRU_ATTR_##_action(CXINF_UPSTREAM_FEC_ERRORS,       u32,  upstream_fec_errors); \
CXACRU_ATTR_##_action(CXINF_DOWNSTREAM_FEC_ERRORS,     u32,  करोwnstream_fec_errors); \
CXACRU_ATTR_##_action(CXINF_UPSTREAM_HEC_ERRORS,       u32,  upstream_hec_errors); \
CXACRU_ATTR_##_action(CXINF_DOWNSTREAM_HEC_ERRORS,     u32,  करोwnstream_hec_errors); \
CXACRU_ATTR_##_action(CXINF_LINE_STARTABLE,            bool, line_startable); \
CXACRU_ATTR_##_action(CXINF_MODULATION,                MODU, modulation); \
CXACRU_ATTR_##_action(CXINF_ADSL_HEADEND,              u32,  adsl_headend); \
CXACRU_ATTR_##_action(CXINF_ADSL_HEADEND_ENVIRONMENT,  u32,  adsl_headend_environment); \
CXACRU_ATTR_##_action(CXINF_CONTROLLER_VERSION,        u32,  adsl_controller_version); \
CXACRU_CMD_##_action(                                        adsl_state); \
CXACRU_SET_##_action(                                        adsl_config);

CXACRU_ALL_खाताS(INIT);

अटल काष्ठा attribute *cxacru_attrs[] = अणु
	&dev_attr_adsl_config.attr,
	&dev_attr_adsl_state.attr,
	&dev_attr_adsl_controller_version.attr,
	&dev_attr_adsl_headend_environment.attr,
	&dev_attr_adsl_headend.attr,
	&dev_attr_modulation.attr,
	&dev_attr_line_startable.attr,
	&dev_attr_करोwnstream_hec_errors.attr,
	&dev_attr_upstream_hec_errors.attr,
	&dev_attr_करोwnstream_fec_errors.attr,
	&dev_attr_upstream_fec_errors.attr,
	&dev_attr_करोwnstream_crc_errors.attr,
	&dev_attr_upstream_crc_errors.attr,
	&dev_attr_startup_attempts.attr,
	&dev_attr_करोwnstream_bits_per_frame.attr,
	&dev_attr_upstream_bits_per_frame.attr,
	&dev_attr_transmitter_घातer.attr,
	&dev_attr_करोwnstream_attenuation.attr,
	&dev_attr_upstream_attenuation.attr,
	&dev_attr_करोwnstream_snr_margin.attr,
	&dev_attr_upstream_snr_margin.attr,
	&dev_attr_mac_address.attr,
	&dev_attr_line_status.attr,
	&dev_attr_link_status.attr,
	&dev_attr_upstream_rate.attr,
	&dev_attr_करोwnstream_rate.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(cxacru);

/* the following three functions are stolen from drivers/usb/core/message.c */
अटल व्योम cxacru_blocking_completion(काष्ठा urb *urb)
अणु
	complete(urb->context);
पूर्ण

काष्ठा cxacru_समयr अणु
	काष्ठा समयr_list समयr;
	काष्ठा urb *urb;
पूर्ण;

अटल व्योम cxacru_समयout_समाप्त(काष्ठा समयr_list *t)
अणु
	काष्ठा cxacru_समयr *समयr = from_समयr(समयr, t, समयr);

	usb_unlink_urb(समयr->urb);
पूर्ण

अटल पूर्णांक cxacru_start_रुको_urb(काष्ठा urb *urb, काष्ठा completion *करोne,
				 पूर्णांक *actual_length)
अणु
	काष्ठा cxacru_समयr समयr = अणु
		.urb = urb,
	पूर्ण;

	समयr_setup_on_stack(&समयr.समयr, cxacru_समयout_समाप्त, 0);
	mod_समयr(&समयr.समयr, jअगरfies + msecs_to_jअगरfies(CMD_TIMEOUT));
	रुको_क्रम_completion(करोne);
	del_समयr_sync(&समयr.समयr);
	destroy_समयr_on_stack(&समयr.समयr);

	अगर (actual_length)
		*actual_length = urb->actual_length;
	वापस urb->status; /* must पढ़ो status after completion */
पूर्ण

अटल पूर्णांक cxacru_cm(काष्ठा cxacru_data *instance, क्रमागत cxacru_cm_request cm,
		     u8 *wdata, पूर्णांक wsize, u8 *rdata, पूर्णांक rsize)
अणु
	पूर्णांक ret, actlen;
	पूर्णांक offb, offd;
	स्थिर पूर्णांक stride = CMD_PACKET_SIZE - 4;
	u8 *wbuf = instance->snd_buf;
	u8 *rbuf = instance->rcv_buf;
	पूर्णांक wbuflen = ((wsize - 1) / stride + 1) * CMD_PACKET_SIZE;
	पूर्णांक rbuflen = ((rsize - 1) / stride + 1) * CMD_PACKET_SIZE;

	अगर (wbuflen > PAGE_SIZE || rbuflen > PAGE_SIZE) अणु
		अगर (prपूर्णांकk_ratelimit())
			usb_err(instance->usbaपंचांग, "requested transfer size too large (%d, %d)\n",
				wbuflen, rbuflen);
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	mutex_lock(&instance->cm_serialize);

	/* submit पढ़ोing urb beक्रमe the writing one */
	init_completion(&instance->rcv_करोne);
	ret = usb_submit_urb(instance->rcv_urb, GFP_KERNEL);
	अगर (ret < 0) अणु
		अगर (prपूर्णांकk_ratelimit())
			usb_err(instance->usbaपंचांग, "submit of read urb for cm %#x failed (%d)\n",
				cm, ret);
		जाओ fail;
	पूर्ण

	स_रखो(wbuf, 0, wbuflen);
	/* handle wsize == 0 */
	wbuf[0] = cm;
	क्रम (offb = offd = 0; offd < wsize; offd += stride, offb += CMD_PACKET_SIZE) अणु
		wbuf[offb] = cm;
		स_नकल(wbuf + offb + 4, wdata + offd, min_t(पूर्णांक, stride, wsize - offd));
	पूर्ण

	instance->snd_urb->transfer_buffer_length = wbuflen;
	init_completion(&instance->snd_करोne);
	ret = usb_submit_urb(instance->snd_urb, GFP_KERNEL);
	अगर (ret < 0) अणु
		अगर (prपूर्णांकk_ratelimit())
			usb_err(instance->usbaपंचांग, "submit of write urb for cm %#x failed (%d)\n",
				cm, ret);
		जाओ fail;
	पूर्ण

	ret = cxacru_start_रुको_urb(instance->snd_urb, &instance->snd_करोne, शून्य);
	अगर (ret < 0) अणु
		अगर (prपूर्णांकk_ratelimit())
			usb_err(instance->usbaपंचांग, "send of cm %#x failed (%d)\n", cm, ret);
		जाओ fail;
	पूर्ण

	ret = cxacru_start_रुको_urb(instance->rcv_urb, &instance->rcv_करोne, &actlen);
	अगर (ret < 0) अणु
		अगर (prपूर्णांकk_ratelimit())
			usb_err(instance->usbaपंचांग, "receive of cm %#x failed (%d)\n", cm, ret);
		जाओ fail;
	पूर्ण
	अगर (actlen % CMD_PACKET_SIZE || !actlen) अणु
		अगर (prपूर्णांकk_ratelimit())
			usb_err(instance->usbaपंचांग, "invalid response length to cm %#x: %d\n",
				cm, actlen);
		ret = -EIO;
		जाओ fail;
	पूर्ण

	/* check the वापस status and copy the data to the output buffer, अगर needed */
	क्रम (offb = offd = 0; offd < rsize && offb < actlen; offb += CMD_PACKET_SIZE) अणु
		अगर (rbuf[offb] != cm) अणु
			अगर (prपूर्णांकk_ratelimit())
				usb_err(instance->usbaपंचांग, "wrong cm %#x in response to cm %#x\n",
					rbuf[offb], cm);
			ret = -EIO;
			जाओ fail;
		पूर्ण
		अगर (rbuf[offb + 1] != CM_STATUS_SUCCESS) अणु
			अगर (prपूर्णांकk_ratelimit())
				usb_err(instance->usbaपंचांग, "response to cm %#x failed: %#x\n",
					cm, rbuf[offb + 1]);
			ret = -EIO;
			जाओ fail;
		पूर्ण
		अगर (offd >= rsize)
			अवरोध;
		स_नकल(rdata + offd, rbuf + offb + 4, min_t(पूर्णांक, stride, rsize - offd));
		offd += stride;
	पूर्ण

	ret = offd;
	usb_dbg(instance->usbaपंचांग, "cm %#x\n", cm);
fail:
	mutex_unlock(&instance->cm_serialize);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक cxacru_cm_get_array(काष्ठा cxacru_data *instance, क्रमागत cxacru_cm_request cm,
			       u32 *data, पूर्णांक size)
अणु
	पूर्णांक ret, len;
	__le32 *buf;
	पूर्णांक offb;
	अचिन्हित पूर्णांक offd;
	स्थिर पूर्णांक stride = CMD_PACKET_SIZE / (4 * 2) - 1;
	पूर्णांक buflen =  ((size - 1) / stride + 1 + size * 2) * 4;

	buf = kदो_स्मृति(buflen, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = cxacru_cm(instance, cm, शून्य, 0, (u8 *) buf, buflen);
	अगर (ret < 0)
		जाओ cleanup;

	/* len > 0 && len % 4 == 0 guaranteed by cxacru_cm() */
	len = ret / 4;
	क्रम (offb = 0; offb < len; ) अणु
		पूर्णांक l = le32_to_cpu(buf[offb++]);

		अगर (l < 0 || l > stride || l > (len - offb) / 2) अणु
			अगर (prपूर्णांकk_ratelimit())
				usb_err(instance->usbaपंचांग, "invalid data length from cm %#x: %d\n",
					cm, l);
			ret = -EIO;
			जाओ cleanup;
		पूर्ण
		जबतक (l--) अणु
			offd = le32_to_cpu(buf[offb++]);
			अगर (offd >= size) अणु
				अगर (prपूर्णांकk_ratelimit())
					usb_err(instance->usbaपंचांग, "wrong index %#x in response to cm %#x\n",
						offd, cm);
				ret = -EIO;
				जाओ cleanup;
			पूर्ण
			data[offd] = le32_to_cpu(buf[offb++]);
		पूर्ण
	पूर्ण

	ret = 0;

cleanup:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक cxacru_card_status(काष्ठा cxacru_data *instance)
अणु
	पूर्णांक ret = cxacru_cm(instance, CM_REQUEST_CARD_GET_STATUS, शून्य, 0, शून्य, 0);

	अगर (ret < 0) अणु		/* firmware not loaded */
		usb_dbg(instance->usbaपंचांग, "cxacru_adsl_start: CARD_GET_STATUS returned %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cxacru_aपंचांग_start(काष्ठा usbaपंचांग_data *usbaपंचांग_instance,
		काष्ठा aपंचांग_dev *aपंचांग_dev)
अणु
	काष्ठा cxacru_data *instance = usbaपंचांग_instance->driver_data;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = usbaपंचांग_instance->usb_पूर्णांकf;
	पूर्णांक ret;
	पूर्णांक start_polling = 1;

	dev_dbg(&पूर्णांकf->dev, "%s\n", __func__);

	/* Read MAC address */
	ret = cxacru_cm(instance, CM_REQUEST_CARD_GET_MAC_ADDRESS, शून्य, 0,
			aपंचांग_dev->esi, माप(aपंचांग_dev->esi));
	अगर (ret < 0) अणु
		aपंचांग_err(usbaपंचांग_instance, "cxacru_atm_start: CARD_GET_MAC_ADDRESS returned %d\n", ret);
		वापस ret;
	पूर्ण

	/* start ADSL */
	mutex_lock(&instance->adsl_state_serialize);
	ret = cxacru_cm(instance, CM_REQUEST_CHIP_ADSL_LINE_START, शून्य, 0, शून्य, 0);
	अगर (ret < 0)
		aपंचांग_err(usbaपंचांग_instance, "cxacru_atm_start: CHIP_ADSL_LINE_START returned %d\n", ret);

	/* Start status polling */
	mutex_lock(&instance->poll_state_serialize);
	चयन (instance->poll_state) अणु
	हाल CXPOLL_STOPPED:
		/* start polling */
		instance->poll_state = CXPOLL_POLLING;
		अवरोध;

	हाल CXPOLL_STOPPING:
		/* पात stop request */
		instance->poll_state = CXPOLL_POLLING;
		fallthrough;
	हाल CXPOLL_POLLING:
	हाल CXPOLL_SHUTDOWN:
		/* करोn't start polling */
		start_polling = 0;
	पूर्ण
	mutex_unlock(&instance->poll_state_serialize);
	mutex_unlock(&instance->adsl_state_serialize);

	अगर (start_polling)
		cxacru_poll_status(&instance->poll_work.work);
	वापस 0;
पूर्ण

अटल व्योम cxacru_poll_status(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cxacru_data *instance =
		container_of(work, काष्ठा cxacru_data, poll_work.work);
	u32 buf[CXINF_MAX] = अणुपूर्ण;
	काष्ठा usbaपंचांग_data *usbaपंचांग = instance->usbaपंचांग;
	काष्ठा aपंचांग_dev *aपंचांग_dev = usbaपंचांग->aपंचांग_dev;
	पूर्णांक keep_polling = 1;
	पूर्णांक ret;

	ret = cxacru_cm_get_array(instance, CM_REQUEST_CARD_INFO_GET, buf, CXINF_MAX);
	अगर (ret < 0) अणु
		अगर (ret != -ESHUTDOWN)
			aपंचांग_warn(usbaपंचांग, "poll status: error %d\n", ret);

		mutex_lock(&instance->poll_state_serialize);
		अगर (instance->poll_state != CXPOLL_SHUTDOWN) अणु
			instance->poll_state = CXPOLL_STOPPED;

			अगर (ret != -ESHUTDOWN)
				aपंचांग_warn(usbaपंचांग, "polling disabled, set adsl_state"
						" to 'start' or 'poll' to resume\n");
		पूर्ण
		mutex_unlock(&instance->poll_state_serialize);
		जाओ reschedule;
	पूर्ण

	स_नकल(instance->card_info, buf, माप(instance->card_info));

	अगर (instance->adsl_status != buf[CXINF_LINE_STARTABLE]) अणु
		instance->adsl_status = buf[CXINF_LINE_STARTABLE];

		चयन (instance->adsl_status) अणु
		हाल 0:
			aपंचांग_info(usbaपंचांग, "ADSL state: running\n");
			अवरोध;

		हाल 1:
			aपंचांग_info(usbaपंचांग, "ADSL state: stopped\n");
			अवरोध;

		शेष:
			aपंचांग_info(usbaपंचांग, "Unknown adsl status %02x\n", instance->adsl_status);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (instance->line_status == buf[CXINF_LINE_STATUS])
		जाओ reschedule;

	instance->line_status = buf[CXINF_LINE_STATUS];
	चयन (instance->line_status) अणु
	हाल 0:
		aपंचांग_dev_संकेत_change(aपंचांग_dev, ATM_PHY_SIG_LOST);
		aपंचांग_info(usbaपंचांग, "ADSL line: down\n");
		अवरोध;

	हाल 1:
		aपंचांग_dev_संकेत_change(aपंचांग_dev, ATM_PHY_SIG_LOST);
		aपंचांग_info(usbaपंचांग, "ADSL line: attempting to activate\n");
		अवरोध;

	हाल 2:
		aपंचांग_dev_संकेत_change(aपंचांग_dev, ATM_PHY_SIG_LOST);
		aपंचांग_info(usbaपंचांग, "ADSL line: training\n");
		अवरोध;

	हाल 3:
		aपंचांग_dev_संकेत_change(aपंचांग_dev, ATM_PHY_SIG_LOST);
		aपंचांग_info(usbaपंचांग, "ADSL line: channel analysis\n");
		अवरोध;

	हाल 4:
		aपंचांग_dev_संकेत_change(aपंचांग_dev, ATM_PHY_SIG_LOST);
		aपंचांग_info(usbaपंचांग, "ADSL line: exchange\n");
		अवरोध;

	हाल 5:
		aपंचांग_dev->link_rate = buf[CXINF_DOWNSTREAM_RATE] * 1000 / 424;
		aपंचांग_dev_संकेत_change(aपंचांग_dev, ATM_PHY_SIG_FOUND);

		aपंचांग_info(usbaपंचांग, "ADSL line: up (%d kb/s down | %d kb/s up)\n",
		     buf[CXINF_DOWNSTREAM_RATE], buf[CXINF_UPSTREAM_RATE]);
		अवरोध;

	हाल 6:
		aपंचांग_dev_संकेत_change(aपंचांग_dev, ATM_PHY_SIG_LOST);
		aपंचांग_info(usbaपंचांग, "ADSL line: waiting\n");
		अवरोध;

	हाल 7:
		aपंचांग_dev_संकेत_change(aपंचांग_dev, ATM_PHY_SIG_LOST);
		aपंचांग_info(usbaपंचांग, "ADSL line: initializing\n");
		अवरोध;

	शेष:
		aपंचांग_dev_संकेत_change(aपंचांग_dev, ATM_PHY_SIG_UNKNOWN);
		aपंचांग_info(usbaपंचांग, "Unknown line state %02x\n", instance->line_status);
		अवरोध;
	पूर्ण
reschedule:

	mutex_lock(&instance->poll_state_serialize);
	अगर (instance->poll_state == CXPOLL_STOPPING &&
				instance->adsl_status == 1 && /* stopped */
				instance->line_status == 0) /* करोwn */
		instance->poll_state = CXPOLL_STOPPED;

	अगर (instance->poll_state == CXPOLL_STOPPED)
		keep_polling = 0;
	mutex_unlock(&instance->poll_state_serialize);

	अगर (keep_polling)
		schedule_delayed_work(&instance->poll_work,
				round_jअगरfies_relative(POLL_INTERVAL*HZ));
पूर्ण

अटल पूर्णांक cxacru_fw(काष्ठा usb_device *usb_dev, क्रमागत cxacru_fw_request fw,
		     u8 code1, u8 code2, u32 addr, स्थिर u8 *data, पूर्णांक size)
अणु
	पूर्णांक ret;
	u8 *buf;
	पूर्णांक offd, offb;
	स्थिर पूर्णांक stride = CMD_PACKET_SIZE - 8;

	buf = (u8 *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	offb = offd = 0;
	करो अणु
		पूर्णांक l = min_t(पूर्णांक, stride, size - offd);

		buf[offb++] = fw;
		buf[offb++] = l;
		buf[offb++] = code1;
		buf[offb++] = code2;
		put_unaligned(cpu_to_le32(addr), (__le32 *)(buf + offb));
		offb += 4;
		addr += l;
		अगर (l)
			स_नकल(buf + offb, data + offd, l);
		अगर (l < stride)
			स_रखो(buf + offb + l, 0, stride - l);
		offb += stride;
		offd += stride;
		अगर ((offb >= PAGE_SIZE) || (offd >= size)) अणु
			ret = usb_bulk_msg(usb_dev, usb_sndbulkpipe(usb_dev, CXACRU_EP_CMD),
					   buf, offb, शून्य, CMD_TIMEOUT);
			अगर (ret < 0) अणु
				dev_dbg(&usb_dev->dev, "sending fw %#x failed\n", fw);
				जाओ cleanup;
			पूर्ण
			offb = 0;
		पूर्ण
	पूर्ण जबतक (offd < size);
	dev_dbg(&usb_dev->dev, "sent fw %#x\n", fw);

	ret = 0;

cleanup:
	मुक्त_page((अचिन्हित दीर्घ) buf);
	वापस ret;
पूर्ण

अटल व्योम cxacru_upload_firmware(काष्ठा cxacru_data *instance,
				   स्थिर काष्ठा firmware *fw,
				   स्थिर काष्ठा firmware *bp)
अणु
	पूर्णांक ret;
	काष्ठा usbaपंचांग_data *usbaपंचांग = instance->usbaपंचांग;
	काष्ठा usb_device *usb_dev = usbaपंचांग->usb_dev;
	__le16 signature[] = अणु usb_dev->descriptor.idVenकरोr,
			       usb_dev->descriptor.idProduct पूर्ण;
	__le32 val;

	usb_dbg(usbaपंचांग, "%s\n", __func__);

	/* FirmwarePllFClkValue */
	val = cpu_to_le32(instance->modem_type->pll_f_clk);
	ret = cxacru_fw(usb_dev, FW_WRITE_MEM, 0x2, 0x0, PLLFCLK_ADDR, (u8 *) &val, 4);
	अगर (ret) अणु
		usb_err(usbaपंचांग, "FirmwarePllFClkValue failed: %d\n", ret);
		वापस;
	पूर्ण

	/* FirmwarePllBClkValue */
	val = cpu_to_le32(instance->modem_type->pll_b_clk);
	ret = cxacru_fw(usb_dev, FW_WRITE_MEM, 0x2, 0x0, PLLBCLK_ADDR, (u8 *) &val, 4);
	अगर (ret) अणु
		usb_err(usbaपंचांग, "FirmwarePllBClkValue failed: %d\n", ret);
		वापस;
	पूर्ण

	/* Enable SDRAM */
	val = cpu_to_le32(SDRAM_ENA);
	ret = cxacru_fw(usb_dev, FW_WRITE_MEM, 0x2, 0x0, SDRAMEN_ADDR, (u8 *) &val, 4);
	अगर (ret) अणु
		usb_err(usbaपंचांग, "Enable SDRAM failed: %d\n", ret);
		वापस;
	पूर्ण

	/* Firmware */
	usb_info(usbaपंचांग, "loading firmware\n");
	ret = cxacru_fw(usb_dev, FW_WRITE_MEM, 0x2, 0x0, FW_ADDR, fw->data, fw->size);
	अगर (ret) अणु
		usb_err(usbaपंचांग, "Firmware upload failed: %d\n", ret);
		वापस;
	पूर्ण

	/* Boot ROM patch */
	अगर (instance->modem_type->boot_rom_patch) अणु
		usb_info(usbaपंचांग, "loading boot ROM patch\n");
		ret = cxacru_fw(usb_dev, FW_WRITE_MEM, 0x2, 0x0, BR_ADDR, bp->data, bp->size);
		अगर (ret) अणु
			usb_err(usbaपंचांग, "Boot ROM patching failed: %d\n", ret);
			वापस;
		पूर्ण
	पूर्ण

	/* Signature */
	ret = cxacru_fw(usb_dev, FW_WRITE_MEM, 0x2, 0x0, SIG_ADDR, (u8 *) signature, 4);
	अगर (ret) अणु
		usb_err(usbaपंचांग, "Signature storing failed: %d\n", ret);
		वापस;
	पूर्ण

	usb_info(usbaपंचांग, "starting device\n");
	अगर (instance->modem_type->boot_rom_patch) अणु
		val = cpu_to_le32(BR_ADDR);
		ret = cxacru_fw(usb_dev, FW_WRITE_MEM, 0x2, 0x0, BR_STACK_ADDR, (u8 *) &val, 4);
	पूर्ण अन्यथा अणु
		ret = cxacru_fw(usb_dev, FW_GOTO_MEM, 0x0, 0x0, FW_ADDR, शून्य, 0);
	पूर्ण
	अगर (ret) अणु
		usb_err(usbaपंचांग, "Passing control to firmware failed: %d\n", ret);
		वापस;
	पूर्ण

	/* Delay to allow firmware to start up. */
	msleep_पूर्णांकerruptible(1000);

	usb_clear_halt(usb_dev, usb_sndbulkpipe(usb_dev, CXACRU_EP_CMD));
	usb_clear_halt(usb_dev, usb_rcvbulkpipe(usb_dev, CXACRU_EP_CMD));
	usb_clear_halt(usb_dev, usb_sndbulkpipe(usb_dev, CXACRU_EP_DATA));
	usb_clear_halt(usb_dev, usb_rcvbulkpipe(usb_dev, CXACRU_EP_DATA));

	ret = cxacru_cm(instance, CM_REQUEST_CARD_GET_STATUS, शून्य, 0, शून्य, 0);
	अगर (ret < 0) अणु
		usb_err(usbaपंचांग, "modem failed to initialize: %d\n", ret);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक cxacru_find_firmware(काष्ठा cxacru_data *instance,
				अक्षर *phase, स्थिर काष्ठा firmware **fw_p)
अणु
	काष्ठा usbaपंचांग_data *usbaपंचांग = instance->usbaपंचांग;
	काष्ठा device *dev = &usbaपंचांग->usb_पूर्णांकf->dev;
	अक्षर buf[16];

	प्र_लिखो(buf, "cxacru-%s.bin", phase);
	usb_dbg(usbaपंचांग, "cxacru_find_firmware: looking for %s\n", buf);

	अगर (request_firmware(fw_p, buf, dev)) अणु
		usb_dbg(usbaपंचांग, "no stage %s firmware found\n", phase);
		वापस -ENOENT;
	पूर्ण

	usb_info(usbaपंचांग, "found firmware %s\n", buf);

	वापस 0;
पूर्ण

अटल पूर्णांक cxacru_heavy_init(काष्ठा usbaपंचांग_data *usbaपंचांग_instance,
			     काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf)
अणु
	स्थिर काष्ठा firmware *fw, *bp;
	काष्ठा cxacru_data *instance = usbaपंचांग_instance->driver_data;
	पूर्णांक ret = cxacru_find_firmware(instance, "fw", &fw);

	अगर (ret) अणु
		usb_warn(usbaपंचांग_instance, "firmware (cxacru-fw.bin) unavailable (system misconfigured?)\n");
		वापस ret;
	पूर्ण

	अगर (instance->modem_type->boot_rom_patch) अणु
		ret = cxacru_find_firmware(instance, "bp", &bp);
		अगर (ret) अणु
			usb_warn(usbaपंचांग_instance, "boot ROM patch (cxacru-bp.bin) unavailable (system misconfigured?)\n");
			release_firmware(fw);
			वापस ret;
		पूर्ण
	पूर्ण

	cxacru_upload_firmware(instance, fw, bp);

	अगर (instance->modem_type->boot_rom_patch)
		release_firmware(bp);
	release_firmware(fw);

	ret = cxacru_card_status(instance);
	अगर (ret)
		usb_dbg(usbaपंचांग_instance, "modem initialisation failed\n");
	अन्यथा
		usb_dbg(usbaपंचांग_instance, "done setting up the modem\n");

	वापस ret;
पूर्ण

अटल पूर्णांक cxacru_bind(काष्ठा usbaपंचांग_data *usbaपंचांग_instance,
		       काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा cxacru_data *instance;
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_host_endpoपूर्णांक *cmd_ep = usb_dev->ep_in[CXACRU_EP_CMD];
	पूर्णांक ret;

	/* instance init */
	instance = kzalloc(माप(*instance), GFP_KERNEL);
	अगर (!instance)
		वापस -ENOMEM;

	instance->usbaपंचांग = usbaपंचांग_instance;
	instance->modem_type = (काष्ठा cxacru_modem_type *) id->driver_info;

	mutex_init(&instance->poll_state_serialize);
	instance->poll_state = CXPOLL_STOPPED;
	instance->line_status = -1;
	instance->adsl_status = -1;

	mutex_init(&instance->adsl_state_serialize);

	instance->rcv_buf = (u8 *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!instance->rcv_buf) अणु
		usb_dbg(usbaपंचांग_instance, "cxacru_bind: no memory for rcv_buf\n");
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	instance->snd_buf = (u8 *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!instance->snd_buf) अणु
		usb_dbg(usbaपंचांग_instance, "cxacru_bind: no memory for snd_buf\n");
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	instance->rcv_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!instance->rcv_urb) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	instance->snd_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!instance->snd_urb) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	अगर (!cmd_ep) अणु
		usb_dbg(usbaपंचांग_instance, "cxacru_bind: no command endpoint\n");
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	अगर ((cmd_ep->desc.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK)
			== USB_ENDPOINT_XFER_INT) अणु
		usb_fill_पूर्णांक_urb(instance->rcv_urb,
			usb_dev, usb_rcvपूर्णांकpipe(usb_dev, CXACRU_EP_CMD),
			instance->rcv_buf, PAGE_SIZE,
			cxacru_blocking_completion, &instance->rcv_करोne, 1);

		usb_fill_पूर्णांक_urb(instance->snd_urb,
			usb_dev, usb_sndपूर्णांकpipe(usb_dev, CXACRU_EP_CMD),
			instance->snd_buf, PAGE_SIZE,
			cxacru_blocking_completion, &instance->snd_करोne, 4);
	पूर्ण अन्यथा अणु
		usb_fill_bulk_urb(instance->rcv_urb,
			usb_dev, usb_rcvbulkpipe(usb_dev, CXACRU_EP_CMD),
			instance->rcv_buf, PAGE_SIZE,
			cxacru_blocking_completion, &instance->rcv_करोne);

		usb_fill_bulk_urb(instance->snd_urb,
			usb_dev, usb_sndbulkpipe(usb_dev, CXACRU_EP_CMD),
			instance->snd_buf, PAGE_SIZE,
			cxacru_blocking_completion, &instance->snd_करोne);
	पूर्ण

	mutex_init(&instance->cm_serialize);

	INIT_DELAYED_WORK(&instance->poll_work, cxacru_poll_status);

	usbaपंचांग_instance->driver_data = instance;

	usbaपंचांग_instance->flags = (cxacru_card_status(instance) ? 0 : UDSL_SKIP_HEAVY_INIT);

	वापस 0;

 fail:
	मुक्त_page((अचिन्हित दीर्घ) instance->snd_buf);
	मुक्त_page((अचिन्हित दीर्घ) instance->rcv_buf);
	usb_मुक्त_urb(instance->snd_urb);
	usb_मुक्त_urb(instance->rcv_urb);
	kमुक्त(instance);

	वापस ret;
पूर्ण

अटल व्योम cxacru_unbind(काष्ठा usbaपंचांग_data *usbaपंचांग_instance,
		काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा cxacru_data *instance = usbaपंचांग_instance->driver_data;
	पूर्णांक is_polling = 1;

	usb_dbg(usbaपंचांग_instance, "cxacru_unbind entered\n");

	अगर (!instance) अणु
		usb_dbg(usbaपंचांग_instance, "cxacru_unbind: NULL instance!\n");
		वापस;
	पूर्ण

	mutex_lock(&instance->poll_state_serialize);
	BUG_ON(instance->poll_state == CXPOLL_SHUTDOWN);

	/* ensure that status polling जारीs unless
	 * it has alपढ़ोy stopped */
	अगर (instance->poll_state == CXPOLL_STOPPED)
		is_polling = 0;

	/* stop polling from being stopped or started */
	instance->poll_state = CXPOLL_SHUTDOWN;
	mutex_unlock(&instance->poll_state_serialize);

	अगर (is_polling)
		cancel_delayed_work_sync(&instance->poll_work);

	usb_समाप्त_urb(instance->snd_urb);
	usb_समाप्त_urb(instance->rcv_urb);
	usb_मुक्त_urb(instance->snd_urb);
	usb_मुक्त_urb(instance->rcv_urb);

	मुक्त_page((अचिन्हित दीर्घ) instance->snd_buf);
	मुक्त_page((अचिन्हित दीर्घ) instance->rcv_buf);

	kमुक्त(instance);

	usbaपंचांग_instance->driver_data = शून्य;
पूर्ण

अटल स्थिर काष्ठा cxacru_modem_type cxacru_cafe = अणु
	.pll_f_clk = 0x02d874df,
	.pll_b_clk = 0x0196a51a,
	.boot_rom_patch = 1,
पूर्ण;

अटल स्थिर काष्ठा cxacru_modem_type cxacru_cb00 = अणु
	.pll_f_clk = 0x5,
	.pll_b_clk = 0x3,
	.boot_rom_patch = 0,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id cxacru_usb_ids[] = अणु
	अणु /* V = Conexant			P = ADSL modem (Euphrates project)	*/
		USB_DEVICE(0x0572, 0xcafe),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cafe
	पूर्ण,
	अणु /* V = Conexant			P = ADSL modem (Hasbani project)	*/
		USB_DEVICE(0x0572, 0xcb00),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cb00
	पूर्ण,
	अणु /* V = Conexant			P = ADSL modem				*/
		USB_DEVICE(0x0572, 0xcb01),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cb00
	पूर्ण,
	अणु /* V = Conexant			P = ADSL modem (Well PTI-800) */
		USB_DEVICE(0x0572, 0xcb02),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cb00
	पूर्ण,
	अणु /* V = Conexant			P = ADSL modem				*/
		USB_DEVICE(0x0572, 0xcb06),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cb00
	पूर्ण,
	अणु /* V = Conexant			P = ADSL modem (ZTE ZXDSL 852)		*/
		USB_DEVICE(0x0572, 0xcb07),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cb00
	पूर्ण,
	अणु /* V = Olitec				P = ADSL modem version 2		*/
		USB_DEVICE(0x08e3, 0x0100),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cafe
	पूर्ण,
	अणु /* V = Olitec				P = ADSL modem version 3		*/
		USB_DEVICE(0x08e3, 0x0102),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cb00
	पूर्ण,
	अणु /* V = Trust/Amigo Technology Co.	P = AMX-CA86U				*/
		USB_DEVICE(0x0eb0, 0x3457),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cafe
	पूर्ण,
	अणु /* V = Zoom				P = 5510				*/
		USB_DEVICE(0x1803, 0x5510),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cb00
	पूर्ण,
	अणु /* V = Draytek			P = Vigor 318				*/
		USB_DEVICE(0x0675, 0x0200),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cb00
	पूर्ण,
	अणु /* V = Zyxel				P = 630-C1 aka OMNI ADSL USB (Annex A)	*/
		USB_DEVICE(0x0586, 0x330a),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cb00
	पूर्ण,
	अणु /* V = Zyxel				P = 630-C3 aka OMNI ADSL USB (Annex B)	*/
		USB_DEVICE(0x0586, 0x330b),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cb00
	पूर्ण,
	अणु /* V = Aethra				P = Starmodem UM1020			*/
		USB_DEVICE(0x0659, 0x0020),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cb00
	पूर्ण,
	अणु /* V = Aztech Systems			P = ? AKA Pirelli AUA-010		*/
		USB_DEVICE(0x0509, 0x0812),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cb00
	पूर्ण,
	अणु /* V = Netopia			P = Cayman 3341(Annex A)/3351(Annex B)	*/
		USB_DEVICE(0x100d, 0xcb01),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cb00
	पूर्ण,
	अणु /* V = Netopia			P = Cayman 3342(Annex A)/3352(Annex B)	*/
		USB_DEVICE(0x100d, 0x3342),	.driver_info = (अचिन्हित दीर्घ) &cxacru_cb00
	पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, cxacru_usb_ids);

अटल काष्ठा usbaपंचांग_driver cxacru_driver = अणु
	.driver_name	= cxacru_driver_name,
	.bind		= cxacru_bind,
	.heavy_init	= cxacru_heavy_init,
	.unbind		= cxacru_unbind,
	.aपंचांग_start	= cxacru_aपंचांग_start,
	.bulk_in	= CXACRU_EP_DATA,
	.bulk_out	= CXACRU_EP_DATA,
	.rx_padding	= 3,
	.tx_padding	= 11,
पूर्ण;

अटल पूर्णांक cxacru_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	अक्षर buf[15];

	/* Aव्योम ADSL routers (cx82310_eth).
	 * Abort अगर bDeviceClass is 0xff and iProduct is "USB NET CARD".
	 */
	अगर (usb_dev->descriptor.bDeviceClass == USB_CLASS_VENDOR_SPEC
			&& usb_string(usb_dev, usb_dev->descriptor.iProduct,
				buf, माप(buf)) > 0) अणु
		अगर (!म_भेद(buf, "USB NET CARD")) अणु
			dev_info(&पूर्णांकf->dev, "ignoring cx82310_eth device\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस usbaपंचांग_usb_probe(पूर्णांकf, id, &cxacru_driver);
पूर्ण

अटल काष्ठा usb_driver cxacru_usb_driver = अणु
	.name		= cxacru_driver_name,
	.probe		= cxacru_usb_probe,
	.disconnect	= usbaपंचांग_usb_disconnect,
	.id_table	= cxacru_usb_ids,
	.dev_groups	= cxacru_groups,
पूर्ण;

module_usb_driver(cxacru_usb_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
