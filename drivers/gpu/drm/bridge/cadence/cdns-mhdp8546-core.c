<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cadence MHDP8546 DP bridge driver.
 *
 * Copyright (C) 2020 Cadence Design Systems, Inc.
 *
 * Authors: Quentin Schulz <quentin.schulz@मुक्त-electrons.com>
 *          Swapnil Jakhade <sjakhade@cadence.com>
 *          Yuti Amonkar <yamonkar@cadence.com>
 *          Tomi Valkeinen <tomi.valkeinen@ti.com>
 *          Jyri Sarha <jsarha@ti.com>
 *
 * TODO:
 *     - Implement optimized mailbox communication using mailbox पूर्णांकerrupts
 *     - Add support क्रम घातer management
 *     - Add support क्रम features like audio, MST and fast link training
 *     - Implement request_fw_cancel to handle HW_STATE
 *     - Fix asynchronous loading of firmware implementation
 *     - Add DRM helper function क्रम cdns_mhdp_lower_link_rate
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/phy-dp.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic_state_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "cdns-mhdp8546-core.h"

#समावेश "cdns-mhdp8546-j721e.h"

अटल पूर्णांक cdns_mhdp_mailbox_पढ़ो(काष्ठा cdns_mhdp_device *mhdp)
अणु
	पूर्णांक ret, empty;

	WARN_ON(!mutex_is_locked(&mhdp->mbox_mutex));

	ret = पढ़ोx_poll_समयout(पढ़ोl, mhdp->regs + CDNS_MAILBOX_EMPTY,
				 empty, !empty, MAILBOX_RETRY_US,
				 MAILBOX_TIMEOUT_US);
	अगर (ret < 0)
		वापस ret;

	वापस पढ़ोl(mhdp->regs + CDNS_MAILBOX_RX_DATA) & 0xff;
पूर्ण

अटल पूर्णांक cdns_mhdp_mailbox_ग_लिखो(काष्ठा cdns_mhdp_device *mhdp, u8 val)
अणु
	पूर्णांक ret, full;

	WARN_ON(!mutex_is_locked(&mhdp->mbox_mutex));

	ret = पढ़ोx_poll_समयout(पढ़ोl, mhdp->regs + CDNS_MAILBOX_FULL,
				 full, !full, MAILBOX_RETRY_US,
				 MAILBOX_TIMEOUT_US);
	अगर (ret < 0)
		वापस ret;

	ग_लिखोl(val, mhdp->regs + CDNS_MAILBOX_TX_DATA);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_mhdp_mailbox_recv_header(काष्ठा cdns_mhdp_device *mhdp,
					 u8 module_id, u8 opcode,
					 u16 req_size)
अणु
	u32 mbox_size, i;
	u8 header[4];
	पूर्णांक ret;

	/* पढ़ो the header of the message */
	क्रम (i = 0; i < माप(header); i++) अणु
		ret = cdns_mhdp_mailbox_पढ़ो(mhdp);
		अगर (ret < 0)
			वापस ret;

		header[i] = ret;
	पूर्ण

	mbox_size = get_unaligned_be16(header + 2);

	अगर (opcode != header[0] || module_id != header[1] ||
	    req_size != mbox_size) अणु
		/*
		 * If the message in mailbox is not what we want, we need to
		 * clear the mailbox by पढ़ोing its contents.
		 */
		क्रम (i = 0; i < mbox_size; i++)
			अगर (cdns_mhdp_mailbox_पढ़ो(mhdp) < 0)
				अवरोध;

		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_mhdp_mailbox_recv_data(काष्ठा cdns_mhdp_device *mhdp,
				       u8 *buff, u16 buff_size)
अणु
	u32 i;
	पूर्णांक ret;

	क्रम (i = 0; i < buff_size; i++) अणु
		ret = cdns_mhdp_mailbox_पढ़ो(mhdp);
		अगर (ret < 0)
			वापस ret;

		buff[i] = ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_mhdp_mailbox_send(काष्ठा cdns_mhdp_device *mhdp, u8 module_id,
				  u8 opcode, u16 size, u8 *message)
अणु
	u8 header[4];
	पूर्णांक ret, i;

	header[0] = opcode;
	header[1] = module_id;
	put_unaligned_be16(size, header + 2);

	क्रम (i = 0; i < माप(header); i++) अणु
		ret = cdns_mhdp_mailbox_ग_लिखो(mhdp, header[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < size; i++) अणु
		ret = cdns_mhdp_mailbox_ग_लिखो(mhdp, message[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल
पूर्णांक cdns_mhdp_reg_पढ़ो(काष्ठा cdns_mhdp_device *mhdp, u32 addr, u32 *value)
अणु
	u8 msg[4], resp[8];
	पूर्णांक ret;

	put_unaligned_be32(addr, msg);

	mutex_lock(&mhdp->mbox_mutex);

	ret = cdns_mhdp_mailbox_send(mhdp, MB_MODULE_ID_GENERAL,
				     GENERAL_REGISTER_READ,
				     माप(msg), msg);
	अगर (ret)
		जाओ out;

	ret = cdns_mhdp_mailbox_recv_header(mhdp, MB_MODULE_ID_GENERAL,
					    GENERAL_REGISTER_READ,
					    माप(resp));
	अगर (ret)
		जाओ out;

	ret = cdns_mhdp_mailbox_recv_data(mhdp, resp, माप(resp));
	अगर (ret)
		जाओ out;

	/* Returned address value should be the same as requested */
	अगर (स_भेद(msg, resp, माप(msg))) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	*value = get_unaligned_be32(resp + 4);

out:
	mutex_unlock(&mhdp->mbox_mutex);
	अगर (ret) अणु
		dev_err(mhdp->dev, "Failed to read register\n");
		*value = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल
पूर्णांक cdns_mhdp_reg_ग_लिखो(काष्ठा cdns_mhdp_device *mhdp, u16 addr, u32 val)
अणु
	u8 msg[6];
	पूर्णांक ret;

	put_unaligned_be16(addr, msg);
	put_unaligned_be32(val, msg + 2);

	mutex_lock(&mhdp->mbox_mutex);

	ret = cdns_mhdp_mailbox_send(mhdp, MB_MODULE_ID_DP_TX,
				     DPTX_WRITE_REGISTER, माप(msg), msg);

	mutex_unlock(&mhdp->mbox_mutex);

	वापस ret;
पूर्ण

अटल
पूर्णांक cdns_mhdp_reg_ग_लिखो_bit(काष्ठा cdns_mhdp_device *mhdp, u16 addr,
			    u8 start_bit, u8 bits_no, u32 val)
अणु
	u8 field[8];
	पूर्णांक ret;

	put_unaligned_be16(addr, field);
	field[2] = start_bit;
	field[3] = bits_no;
	put_unaligned_be32(val, field + 4);

	mutex_lock(&mhdp->mbox_mutex);

	ret = cdns_mhdp_mailbox_send(mhdp, MB_MODULE_ID_DP_TX,
				     DPTX_WRITE_FIELD, माप(field), field);

	mutex_unlock(&mhdp->mbox_mutex);

	वापस ret;
पूर्ण

अटल
पूर्णांक cdns_mhdp_dpcd_पढ़ो(काष्ठा cdns_mhdp_device *mhdp,
			u32 addr, u8 *data, u16 len)
अणु
	u8 msg[5], reg[5];
	पूर्णांक ret;

	put_unaligned_be16(len, msg);
	put_unaligned_be24(addr, msg + 2);

	mutex_lock(&mhdp->mbox_mutex);

	ret = cdns_mhdp_mailbox_send(mhdp, MB_MODULE_ID_DP_TX,
				     DPTX_READ_DPCD, माप(msg), msg);
	अगर (ret)
		जाओ out;

	ret = cdns_mhdp_mailbox_recv_header(mhdp, MB_MODULE_ID_DP_TX,
					    DPTX_READ_DPCD,
					    माप(reg) + len);
	अगर (ret)
		जाओ out;

	ret = cdns_mhdp_mailbox_recv_data(mhdp, reg, माप(reg));
	अगर (ret)
		जाओ out;

	ret = cdns_mhdp_mailbox_recv_data(mhdp, data, len);

out:
	mutex_unlock(&mhdp->mbox_mutex);

	वापस ret;
पूर्ण

अटल
पूर्णांक cdns_mhdp_dpcd_ग_लिखो(काष्ठा cdns_mhdp_device *mhdp, u32 addr, u8 value)
अणु
	u8 msg[6], reg[5];
	पूर्णांक ret;

	put_unaligned_be16(1, msg);
	put_unaligned_be24(addr, msg + 2);
	msg[5] = value;

	mutex_lock(&mhdp->mbox_mutex);

	ret = cdns_mhdp_mailbox_send(mhdp, MB_MODULE_ID_DP_TX,
				     DPTX_WRITE_DPCD, माप(msg), msg);
	अगर (ret)
		जाओ out;

	ret = cdns_mhdp_mailbox_recv_header(mhdp, MB_MODULE_ID_DP_TX,
					    DPTX_WRITE_DPCD, माप(reg));
	अगर (ret)
		जाओ out;

	ret = cdns_mhdp_mailbox_recv_data(mhdp, reg, माप(reg));
	अगर (ret)
		जाओ out;

	अगर (addr != get_unaligned_be24(reg + 2))
		ret = -EINVAL;

out:
	mutex_unlock(&mhdp->mbox_mutex);

	अगर (ret)
		dev_err(mhdp->dev, "dpcd write failed: %d\n", ret);
	वापस ret;
पूर्ण

अटल
पूर्णांक cdns_mhdp_set_firmware_active(काष्ठा cdns_mhdp_device *mhdp, bool enable)
अणु
	u8 msg[5];
	पूर्णांक ret, i;

	msg[0] = GENERAL_MAIN_CONTROL;
	msg[1] = MB_MODULE_ID_GENERAL;
	msg[2] = 0;
	msg[3] = 1;
	msg[4] = enable ? FW_ACTIVE : FW_STANDBY;

	mutex_lock(&mhdp->mbox_mutex);

	क्रम (i = 0; i < माप(msg); i++) अणु
		ret = cdns_mhdp_mailbox_ग_लिखो(mhdp, msg[i]);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* पढ़ो the firmware state */
	ret = cdns_mhdp_mailbox_recv_data(mhdp, msg, माप(msg));
	अगर (ret)
		जाओ out;

	ret = 0;

out:
	mutex_unlock(&mhdp->mbox_mutex);

	अगर (ret < 0)
		dev_err(mhdp->dev, "set firmware active failed\n");
	वापस ret;
पूर्ण

अटल
पूर्णांक cdns_mhdp_get_hpd_status(काष्ठा cdns_mhdp_device *mhdp)
अणु
	u8 status;
	पूर्णांक ret;

	mutex_lock(&mhdp->mbox_mutex);

	ret = cdns_mhdp_mailbox_send(mhdp, MB_MODULE_ID_DP_TX,
				     DPTX_HPD_STATE, 0, शून्य);
	अगर (ret)
		जाओ err_get_hpd;

	ret = cdns_mhdp_mailbox_recv_header(mhdp, MB_MODULE_ID_DP_TX,
					    DPTX_HPD_STATE,
					    माप(status));
	अगर (ret)
		जाओ err_get_hpd;

	ret = cdns_mhdp_mailbox_recv_data(mhdp, &status, माप(status));
	अगर (ret)
		जाओ err_get_hpd;

	mutex_unlock(&mhdp->mbox_mutex);

	dev_dbg(mhdp->dev, "%s: HPD %splugged\n", __func__,
		status ? "" : "un");

	वापस status;

err_get_hpd:
	mutex_unlock(&mhdp->mbox_mutex);

	वापस ret;
पूर्ण

अटल
पूर्णांक cdns_mhdp_get_edid_block(व्योम *data, u8 *edid,
			     अचिन्हित पूर्णांक block, माप_प्रकार length)
अणु
	काष्ठा cdns_mhdp_device *mhdp = data;
	u8 msg[2], reg[2], i;
	पूर्णांक ret;

	mutex_lock(&mhdp->mbox_mutex);

	क्रम (i = 0; i < 4; i++) अणु
		msg[0] = block / 2;
		msg[1] = block % 2;

		ret = cdns_mhdp_mailbox_send(mhdp, MB_MODULE_ID_DP_TX,
					     DPTX_GET_EDID, माप(msg), msg);
		अगर (ret)
			जारी;

		ret = cdns_mhdp_mailbox_recv_header(mhdp, MB_MODULE_ID_DP_TX,
						    DPTX_GET_EDID,
						    माप(reg) + length);
		अगर (ret)
			जारी;

		ret = cdns_mhdp_mailbox_recv_data(mhdp, reg, माप(reg));
		अगर (ret)
			जारी;

		ret = cdns_mhdp_mailbox_recv_data(mhdp, edid, length);
		अगर (ret)
			जारी;

		अगर (reg[0] == length && reg[1] == block / 2)
			अवरोध;
	पूर्ण

	mutex_unlock(&mhdp->mbox_mutex);

	अगर (ret)
		dev_err(mhdp->dev, "get block[%d] edid failed: %d\n",
			block, ret);

	वापस ret;
पूर्ण

अटल
पूर्णांक cdns_mhdp_पढ़ो_hpd_event(काष्ठा cdns_mhdp_device *mhdp)
अणु
	u8 event = 0;
	पूर्णांक ret;

	mutex_lock(&mhdp->mbox_mutex);

	ret = cdns_mhdp_mailbox_send(mhdp, MB_MODULE_ID_DP_TX,
				     DPTX_READ_EVENT, 0, शून्य);
	अगर (ret)
		जाओ out;

	ret = cdns_mhdp_mailbox_recv_header(mhdp, MB_MODULE_ID_DP_TX,
					    DPTX_READ_EVENT, माप(event));
	अगर (ret < 0)
		जाओ out;

	ret = cdns_mhdp_mailbox_recv_data(mhdp, &event, माप(event));
out:
	mutex_unlock(&mhdp->mbox_mutex);

	अगर (ret < 0)
		वापस ret;

	dev_dbg(mhdp->dev, "%s: %s%s%s%s\n", __func__,
		(event & DPTX_READ_EVENT_HPD_TO_HIGH) ? "TO_HIGH " : "",
		(event & DPTX_READ_EVENT_HPD_TO_LOW) ? "TO_LOW " : "",
		(event & DPTX_READ_EVENT_HPD_PULSE) ? "PULSE " : "",
		(event & DPTX_READ_EVENT_HPD_STATE) ? "HPD_STATE " : "");

	वापस event;
पूर्ण

अटल
पूर्णांक cdns_mhdp_adjust_lt(काष्ठा cdns_mhdp_device *mhdp, अचिन्हित पूर्णांक nlanes,
			अचिन्हित पूर्णांक udelay, स्थिर u8 *lanes_data,
			u8 link_status[DP_LINK_STATUS_SIZE])
अणु
	u8 payload[7];
	u8 hdr[5]; /* For DPCD पढ़ो response header */
	u32 addr;
	पूर्णांक ret;

	अगर (nlanes != 4 && nlanes != 2 && nlanes != 1) अणु
		dev_err(mhdp->dev, "invalid number of lanes: %u\n", nlanes);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	payload[0] = nlanes;
	put_unaligned_be16(udelay, payload + 1);
	स_नकल(payload + 3, lanes_data, nlanes);

	mutex_lock(&mhdp->mbox_mutex);

	ret = cdns_mhdp_mailbox_send(mhdp, MB_MODULE_ID_DP_TX,
				     DPTX_ADJUST_LT,
				     माप(payload), payload);
	अगर (ret)
		जाओ out;

	/* Yes, पढ़ो the DPCD पढ़ो command response */
	ret = cdns_mhdp_mailbox_recv_header(mhdp, MB_MODULE_ID_DP_TX,
					    DPTX_READ_DPCD,
					    माप(hdr) + DP_LINK_STATUS_SIZE);
	अगर (ret)
		जाओ out;

	ret = cdns_mhdp_mailbox_recv_data(mhdp, hdr, माप(hdr));
	अगर (ret)
		जाओ out;

	addr = get_unaligned_be24(hdr + 2);
	अगर (addr != DP_LANE0_1_STATUS)
		जाओ out;

	ret = cdns_mhdp_mailbox_recv_data(mhdp, link_status,
					  DP_LINK_STATUS_SIZE);

out:
	mutex_unlock(&mhdp->mbox_mutex);

	अगर (ret)
		dev_err(mhdp->dev, "Failed to adjust Link Training.\n");

	वापस ret;
पूर्ण

/**
 * cdns_mhdp_link_घातer_up() - घातer up a DisplayPort link
 * @aux: DisplayPort AUX channel
 * @link: poपूर्णांकer to a काष्ठाure containing the link configuration
 *
 * Returns 0 on success or a negative error code on failure.
 */
अटल
पूर्णांक cdns_mhdp_link_घातer_up(काष्ठा drm_dp_aux *aux, काष्ठा cdns_mhdp_link *link)
अणु
	u8 value;
	पूर्णांक err;

	/* DP_SET_POWER रेजिस्टर is only available on DPCD v1.1 and later */
	अगर (link->revision < 0x11)
		वापस 0;

	err = drm_dp_dpcd_पढ़ोb(aux, DP_SET_POWER, &value);
	अगर (err < 0)
		वापस err;

	value &= ~DP_SET_POWER_MASK;
	value |= DP_SET_POWER_D0;

	err = drm_dp_dpcd_ग_लिखोb(aux, DP_SET_POWER, value);
	अगर (err < 0)
		वापस err;

	/*
	 * According to the DP 1.1 specअगरication, a "Sink Device must निकास the
	 * घातer saving state within 1 ms" (Section 2.5.3.1, Table 5-52, "Sink
	 * Control Field" (रेजिस्टर 0x600).
	 */
	usleep_range(1000, 2000);

	वापस 0;
पूर्ण

/**
 * cdns_mhdp_link_घातer_करोwn() - घातer करोwn a DisplayPort link
 * @aux: DisplayPort AUX channel
 * @link: poपूर्णांकer to a काष्ठाure containing the link configuration
 *
 * Returns 0 on success or a negative error code on failure.
 */
अटल
पूर्णांक cdns_mhdp_link_घातer_करोwn(काष्ठा drm_dp_aux *aux,
			      काष्ठा cdns_mhdp_link *link)
अणु
	u8 value;
	पूर्णांक err;

	/* DP_SET_POWER रेजिस्टर is only available on DPCD v1.1 and later */
	अगर (link->revision < 0x11)
		वापस 0;

	err = drm_dp_dpcd_पढ़ोb(aux, DP_SET_POWER, &value);
	अगर (err < 0)
		वापस err;

	value &= ~DP_SET_POWER_MASK;
	value |= DP_SET_POWER_D3;

	err = drm_dp_dpcd_ग_लिखोb(aux, DP_SET_POWER, value);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

/**
 * cdns_mhdp_link_configure() - configure a DisplayPort link
 * @aux: DisplayPort AUX channel
 * @link: poपूर्णांकer to a काष्ठाure containing the link configuration
 *
 * Returns 0 on success or a negative error code on failure.
 */
अटल
पूर्णांक cdns_mhdp_link_configure(काष्ठा drm_dp_aux *aux,
			     काष्ठा cdns_mhdp_link *link)
अणु
	u8 values[2];
	पूर्णांक err;

	values[0] = drm_dp_link_rate_to_bw_code(link->rate);
	values[1] = link->num_lanes;

	अगर (link->capabilities & DP_LINK_CAP_ENHANCED_FRAMING)
		values[1] |= DP_LANE_COUNT_ENHANCED_FRAME_EN;

	err = drm_dp_dpcd_ग_लिखो(aux, DP_LINK_BW_SET, values, माप(values));
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक cdns_mhdp_max_link_rate(काष्ठा cdns_mhdp_device *mhdp)
अणु
	वापस min(mhdp->host.link_rate, mhdp->sink.link_rate);
पूर्ण

अटल u8 cdns_mhdp_max_num_lanes(काष्ठा cdns_mhdp_device *mhdp)
अणु
	वापस min(mhdp->sink.lanes_cnt, mhdp->host.lanes_cnt);
पूर्ण

अटल u8 cdns_mhdp_eq_training_pattern_supported(काष्ठा cdns_mhdp_device *mhdp)
अणु
	वापस fls(mhdp->host.pattern_supp & mhdp->sink.pattern_supp);
पूर्ण

अटल bool cdns_mhdp_get_ssc_supported(काष्ठा cdns_mhdp_device *mhdp)
अणु
	/* Check अगर SSC is supported by both sides */
	वापस mhdp->host.ssc && mhdp->sink.ssc;
पूर्ण

अटल क्रमागत drm_connector_status cdns_mhdp_detect(काष्ठा cdns_mhdp_device *mhdp)
अणु
	dev_dbg(mhdp->dev, "%s: %d\n", __func__, mhdp->plugged);

	अगर (mhdp->plugged)
		वापस connector_status_connected;
	अन्यथा
		वापस connector_status_disconnected;
पूर्ण

अटल पूर्णांक cdns_mhdp_check_fw_version(काष्ठा cdns_mhdp_device *mhdp)
अणु
	u32 major_num, minor_num, revision;
	u32 fw_ver, lib_ver;

	fw_ver = (पढ़ोl(mhdp->regs + CDNS_VER_H) << 8)
	       | पढ़ोl(mhdp->regs + CDNS_VER_L);

	lib_ver = (पढ़ोl(mhdp->regs + CDNS_LIB_H_ADDR) << 8)
		| पढ़ोl(mhdp->regs + CDNS_LIB_L_ADDR);

	अगर (lib_ver < 33984) अणु
		/*
		 * Older FW versions with major number 1, used to store FW
		 * version inक्रमmation by storing repository revision number
		 * in रेजिस्टरs. This is क्रम identअगरying these FW versions.
		 */
		major_num = 1;
		minor_num = 2;
		अगर (fw_ver == 26098) अणु
			revision = 15;
		पूर्ण अन्यथा अगर (lib_ver == 0 && fw_ver == 0) अणु
			revision = 17;
		पूर्ण अन्यथा अणु
			dev_err(mhdp->dev, "Unsupported FW version: fw_ver = %u, lib_ver = %u\n",
				fw_ver, lib_ver);
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* To identअगरy newer FW versions with major number 2 onwards. */
		major_num = fw_ver / 10000;
		minor_num = (fw_ver / 100) % 100;
		revision = (fw_ver % 10000) % 100;
	पूर्ण

	dev_dbg(mhdp->dev, "FW version: v%u.%u.%u\n", major_num, minor_num,
		revision);
	वापस 0;
पूर्ण

अटल पूर्णांक cdns_mhdp_fw_activate(स्थिर काष्ठा firmware *fw,
				 काष्ठा cdns_mhdp_device *mhdp)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	/* Release uCPU reset and stall it. */
	ग_लिखोl(CDNS_CPU_STALL, mhdp->regs + CDNS_APB_CTRL);

	स_नकल_toio(mhdp->regs + CDNS_MHDP_IMEM, fw->data, fw->size);

	/* Leave debug mode, release stall */
	ग_लिखोl(0, mhdp->regs + CDNS_APB_CTRL);

	/*
	 * Wait क्रम the KEEP_ALIVE "message" on the first 8 bits.
	 * Updated each sched "tick" (~2ms)
	 */
	ret = पढ़ोl_poll_समयout(mhdp->regs + CDNS_KEEP_ALIVE, reg,
				 reg & CDNS_KEEP_ALIVE_MASK, 500,
				 CDNS_KEEP_ALIVE_TIMEOUT);
	अगर (ret) अणु
		dev_err(mhdp->dev,
			"device didn't give any life sign: reg %d\n", reg);
		वापस ret;
	पूर्ण

	ret = cdns_mhdp_check_fw_version(mhdp);
	अगर (ret)
		वापस ret;

	/* Init events to 0 as it's not cleared by FW at boot but on पढ़ो */
	पढ़ोl(mhdp->regs + CDNS_SW_EVENT0);
	पढ़ोl(mhdp->regs + CDNS_SW_EVENT1);
	पढ़ोl(mhdp->regs + CDNS_SW_EVENT2);
	पढ़ोl(mhdp->regs + CDNS_SW_EVENT3);

	/* Activate uCPU */
	ret = cdns_mhdp_set_firmware_active(mhdp, true);
	अगर (ret)
		वापस ret;

	spin_lock(&mhdp->start_lock);

	mhdp->hw_state = MHDP_HW_READY;

	/*
	 * Here we must keep the lock जबतक enabling the पूर्णांकerrupts
	 * since it would otherwise be possible that पूर्णांकerrupt enable
	 * code is executed after the bridge is detached. The similar
	 * situation is not possible in attach()/detach() callbacks
	 * since the hw_state changes from MHDP_HW_READY to
	 * MHDP_HW_STOPPED happens only due to driver removal when
	 * bridge should alपढ़ोy be detached.
	 */
	अगर (mhdp->bridge_attached)
		ग_लिखोl(~(u32)CDNS_APB_INT_MASK_SW_EVENT_INT,
		       mhdp->regs + CDNS_APB_INT_MASK);

	spin_unlock(&mhdp->start_lock);

	wake_up(&mhdp->fw_load_wq);
	dev_dbg(mhdp->dev, "DP FW activated\n");

	वापस 0;
पूर्ण

अटल व्योम cdns_mhdp_fw_cb(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा cdns_mhdp_device *mhdp = context;
	bool bridge_attached;
	पूर्णांक ret;

	dev_dbg(mhdp->dev, "firmware callback\n");

	अगर (!fw || !fw->data) अणु
		dev_err(mhdp->dev, "%s: No firmware.\n", __func__);
		वापस;
	पूर्ण

	ret = cdns_mhdp_fw_activate(fw, mhdp);

	release_firmware(fw);

	अगर (ret)
		वापस;

	/*
	 *  XXX how to make sure the bridge is still attached when
	 *      calling drm_kms_helper_hotplug_event() after releasing
	 *      the lock? We should not hold the spin lock when
	 *      calling drm_kms_helper_hotplug_event() since it may
	 *      cause a dead lock. FB-dev console calls detect from the
	 *      same thपढ़ो just करोwn the call stack started here.
	 */
	spin_lock(&mhdp->start_lock);
	bridge_attached = mhdp->bridge_attached;
	spin_unlock(&mhdp->start_lock);
	अगर (bridge_attached) अणु
		अगर (mhdp->connector.dev)
			drm_kms_helper_hotplug_event(mhdp->bridge.dev);
		अन्यथा
			drm_bridge_hpd_notअगरy(&mhdp->bridge, cdns_mhdp_detect(mhdp));
	पूर्ण
पूर्ण

अटल पूर्णांक cdns_mhdp_load_firmware(काष्ठा cdns_mhdp_device *mhdp)
अणु
	पूर्णांक ret;

	ret = request_firmware_noरुको(THIS_MODULE, true, FW_NAME, mhdp->dev,
				      GFP_KERNEL, mhdp, cdns_mhdp_fw_cb);
	अगर (ret) अणु
		dev_err(mhdp->dev, "failed to load firmware (%s), ret: %d\n",
			FW_NAME, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार cdns_mhdp_transfer(काष्ठा drm_dp_aux *aux,
				  काष्ठा drm_dp_aux_msg *msg)
अणु
	काष्ठा cdns_mhdp_device *mhdp = dev_get_drvdata(aux->dev);
	पूर्णांक ret;

	अगर (msg->request != DP_AUX_NATIVE_WRITE &&
	    msg->request != DP_AUX_NATIVE_READ)
		वापस -EOPNOTSUPP;

	अगर (msg->request == DP_AUX_NATIVE_WRITE) अणु
		स्थिर u8 *buf = msg->buffer;
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < msg->size; ++i) अणु
			ret = cdns_mhdp_dpcd_ग_लिखो(mhdp,
						   msg->address + i, buf[i]);
			अगर (!ret)
				जारी;

			dev_err(mhdp->dev,
				"Failed to write DPCD addr %u\n",
				msg->address + i);

			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = cdns_mhdp_dpcd_पढ़ो(mhdp, msg->address,
					  msg->buffer, msg->size);
		अगर (ret) अणु
			dev_err(mhdp->dev,
				"Failed to read DPCD addr %u\n",
				msg->address);

			वापस ret;
		पूर्ण
	पूर्ण

	वापस msg->size;
पूर्ण

अटल पूर्णांक cdns_mhdp_link_training_init(काष्ठा cdns_mhdp_device *mhdp)
अणु
	जोड़ phy_configure_opts phy_cfg;
	u32 reg32;
	पूर्णांक ret;

	drm_dp_dpcd_ग_लिखोb(&mhdp->aux, DP_TRAINING_PATTERN_SET,
			   DP_TRAINING_PATTERN_DISABLE);

	/* Reset PHY configuration */
	reg32 = CDNS_PHY_COMMON_CONFIG | CDNS_PHY_TRAINING_TYPE(1);
	अगर (!mhdp->host.scrambler)
		reg32 |= CDNS_PHY_SCRAMBLER_BYPASS;

	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DPTX_PHY_CONFIG, reg32);

	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_ENHNCD,
			    mhdp->sink.enhanced & mhdp->host.enhanced);

	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_LANE_EN,
			    CDNS_DP_LANE_EN_LANES(mhdp->link.num_lanes));

	cdns_mhdp_link_configure(&mhdp->aux, &mhdp->link);
	phy_cfg.dp.link_rate = mhdp->link.rate / 100;
	phy_cfg.dp.lanes = mhdp->link.num_lanes;

	स_रखो(phy_cfg.dp.voltage, 0, माप(phy_cfg.dp.voltage));
	स_रखो(phy_cfg.dp.pre, 0, माप(phy_cfg.dp.pre));

	phy_cfg.dp.ssc = cdns_mhdp_get_ssc_supported(mhdp);
	phy_cfg.dp.set_lanes = true;
	phy_cfg.dp.set_rate = true;
	phy_cfg.dp.set_voltages = true;
	ret = phy_configure(mhdp->phy,  &phy_cfg);
	अगर (ret) अणु
		dev_err(mhdp->dev, "%s: phy_configure() failed: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DPTX_PHY_CONFIG,
			    CDNS_PHY_COMMON_CONFIG |
			    CDNS_PHY_TRAINING_EN |
			    CDNS_PHY_TRAINING_TYPE(1) |
			    CDNS_PHY_SCRAMBLER_BYPASS);

	drm_dp_dpcd_ग_लिखोb(&mhdp->aux, DP_TRAINING_PATTERN_SET,
			   DP_TRAINING_PATTERN_1 | DP_LINK_SCRAMBLING_DISABLE);

	वापस 0;
पूर्ण

अटल व्योम cdns_mhdp_get_adjust_train(काष्ठा cdns_mhdp_device *mhdp,
				       u8 link_status[DP_LINK_STATUS_SIZE],
				       u8 lanes_data[CDNS_DP_MAX_NUM_LANES],
				       जोड़ phy_configure_opts *phy_cfg)
अणु
	u8 adjust, max_pre_emph, max_volt_swing;
	u8 set_volt, set_pre;
	अचिन्हित पूर्णांक i;

	max_pre_emph = CDNS_PRE_EMPHASIS(mhdp->host.pre_emphasis)
			   << DP_TRAIN_PRE_EMPHASIS_SHIFT;
	max_volt_swing = CDNS_VOLT_SWING(mhdp->host.volt_swing);

	क्रम (i = 0; i < mhdp->link.num_lanes; i++) अणु
		/* Check अगर Voltage swing and pre-emphasis are within limits */
		adjust = drm_dp_get_adjust_request_voltage(link_status, i);
		set_volt = min(adjust, max_volt_swing);

		adjust = drm_dp_get_adjust_request_pre_emphasis(link_status, i);
		set_pre = min(adjust, max_pre_emph)
			  >> DP_TRAIN_PRE_EMPHASIS_SHIFT;

		/*
		 * Voltage swing level and pre-emphasis level combination is
		 * not allowed: leaving pre-emphasis as-is, and adjusting
		 * voltage swing.
		 */
		अगर (set_volt + set_pre > 3)
			set_volt = 3 - set_pre;

		phy_cfg->dp.voltage[i] = set_volt;
		lanes_data[i] = set_volt;

		अगर (set_volt == max_volt_swing)
			lanes_data[i] |= DP_TRAIN_MAX_SWING_REACHED;

		phy_cfg->dp.pre[i] = set_pre;
		lanes_data[i] |= (set_pre << DP_TRAIN_PRE_EMPHASIS_SHIFT);

		अगर (set_pre == (max_pre_emph >> DP_TRAIN_PRE_EMPHASIS_SHIFT))
			lanes_data[i] |= DP_TRAIN_MAX_PRE_EMPHASIS_REACHED;
	पूर्ण
पूर्ण

अटल
व्योम cdns_mhdp_set_adjust_request_voltage(u8 link_status[DP_LINK_STATUS_SIZE],
					  अचिन्हित पूर्णांक lane, u8 volt)
अणु
	अचिन्हित पूर्णांक s = ((lane & 1) ?
			  DP_ADJUST_VOLTAGE_SWING_LANE1_SHIFT :
			  DP_ADJUST_VOLTAGE_SWING_LANE0_SHIFT);
	अचिन्हित पूर्णांक idx = DP_ADJUST_REQUEST_LANE0_1 - DP_LANE0_1_STATUS + (lane >> 1);

	link_status[idx] &= ~(DP_ADJUST_VOLTAGE_SWING_LANE0_MASK << s);
	link_status[idx] |= volt << s;
पूर्ण

अटल
व्योम cdns_mhdp_set_adjust_request_pre_emphasis(u8 link_status[DP_LINK_STATUS_SIZE],
					       अचिन्हित पूर्णांक lane, u8 pre_emphasis)
अणु
	अचिन्हित पूर्णांक s = ((lane & 1) ?
			  DP_ADJUST_PRE_EMPHASIS_LANE1_SHIFT :
			  DP_ADJUST_PRE_EMPHASIS_LANE0_SHIFT);
	अचिन्हित पूर्णांक idx = DP_ADJUST_REQUEST_LANE0_1 - DP_LANE0_1_STATUS + (lane >> 1);

	link_status[idx] &= ~(DP_ADJUST_PRE_EMPHASIS_LANE0_MASK << s);
	link_status[idx] |= pre_emphasis << s;
पूर्ण

अटल व्योम cdns_mhdp_adjust_requested_eq(काष्ठा cdns_mhdp_device *mhdp,
					  u8 link_status[DP_LINK_STATUS_SIZE])
अणु
	u8 max_pre = CDNS_PRE_EMPHASIS(mhdp->host.pre_emphasis);
	u8 max_volt = CDNS_VOLT_SWING(mhdp->host.volt_swing);
	अचिन्हित पूर्णांक i;
	u8 volt, pre;

	क्रम (i = 0; i < mhdp->link.num_lanes; i++) अणु
		volt = drm_dp_get_adjust_request_voltage(link_status, i);
		pre = drm_dp_get_adjust_request_pre_emphasis(link_status, i);
		अगर (volt + pre > 3)
			cdns_mhdp_set_adjust_request_voltage(link_status, i,
							     3 - pre);
		अगर (mhdp->host.volt_swing & CDNS_FORCE_VOLT_SWING)
			cdns_mhdp_set_adjust_request_voltage(link_status, i,
							     max_volt);
		अगर (mhdp->host.pre_emphasis & CDNS_FORCE_PRE_EMPHASIS)
			cdns_mhdp_set_adjust_request_pre_emphasis(link_status,
								  i, max_pre);
	पूर्ण
पूर्ण

अटल व्योम cdns_mhdp_prपूर्णांक_lt_status(स्थिर अक्षर *prefix,
				      काष्ठा cdns_mhdp_device *mhdp,
				      जोड़ phy_configure_opts *phy_cfg)
अणु
	अक्षर vs[8] = "0/0/0/0";
	अक्षर pe[8] = "0/0/0/0";
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < mhdp->link.num_lanes; i++) अणु
		vs[i * 2] = '0' + phy_cfg->dp.voltage[i];
		pe[i * 2] = '0' + phy_cfg->dp.pre[i];
	पूर्ण

	vs[i * 2 - 1] = '\0';
	pe[i * 2 - 1] = '\0';

	dev_dbg(mhdp->dev, "%s, %u lanes, %u Mbps, vs %s, pe %s\n",
		prefix,
		mhdp->link.num_lanes, mhdp->link.rate / 100,
		vs, pe);
पूर्ण

अटल bool cdns_mhdp_link_training_channel_eq(काष्ठा cdns_mhdp_device *mhdp,
					       u8 eq_tps,
					       अचिन्हित पूर्णांक training_पूर्णांकerval)
अणु
	u8 lanes_data[CDNS_DP_MAX_NUM_LANES], fail_counter_लघु = 0;
	u8 link_status[DP_LINK_STATUS_SIZE];
	जोड़ phy_configure_opts phy_cfg;
	u32 reg32;
	पूर्णांक ret;
	bool r;

	dev_dbg(mhdp->dev, "Starting EQ phase\n");

	/* Enable link training TPS[eq_tps] in PHY */
	reg32 = CDNS_PHY_COMMON_CONFIG | CDNS_PHY_TRAINING_EN |
		CDNS_PHY_TRAINING_TYPE(eq_tps);
	अगर (eq_tps != 4)
		reg32 |= CDNS_PHY_SCRAMBLER_BYPASS;
	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DPTX_PHY_CONFIG, reg32);

	drm_dp_dpcd_ग_लिखोb(&mhdp->aux, DP_TRAINING_PATTERN_SET,
			   (eq_tps != 4) ? eq_tps | DP_LINK_SCRAMBLING_DISABLE :
			   CDNS_DP_TRAINING_PATTERN_4);

	drm_dp_dpcd_पढ़ो_link_status(&mhdp->aux, link_status);

	करो अणु
		cdns_mhdp_get_adjust_train(mhdp, link_status, lanes_data,
					   &phy_cfg);
		phy_cfg.dp.lanes = mhdp->link.num_lanes;
		phy_cfg.dp.ssc = cdns_mhdp_get_ssc_supported(mhdp);
		phy_cfg.dp.set_lanes = false;
		phy_cfg.dp.set_rate = false;
		phy_cfg.dp.set_voltages = true;
		ret = phy_configure(mhdp->phy,  &phy_cfg);
		अगर (ret) अणु
			dev_err(mhdp->dev, "%s: phy_configure() failed: %d\n",
				__func__, ret);
			जाओ err;
		पूर्ण

		cdns_mhdp_adjust_lt(mhdp, mhdp->link.num_lanes,
				    training_पूर्णांकerval, lanes_data, link_status);

		r = drm_dp_घड़ी_recovery_ok(link_status, mhdp->link.num_lanes);
		अगर (!r)
			जाओ err;

		अगर (drm_dp_channel_eq_ok(link_status, mhdp->link.num_lanes)) अणु
			cdns_mhdp_prपूर्णांक_lt_status("EQ phase ok", mhdp,
						  &phy_cfg);
			वापस true;
		पूर्ण

		fail_counter_लघु++;

		cdns_mhdp_adjust_requested_eq(mhdp, link_status);
	पूर्ण जबतक (fail_counter_लघु < 5);

err:
	cdns_mhdp_prपूर्णांक_lt_status("EQ phase failed", mhdp, &phy_cfg);

	वापस false;
पूर्ण

अटल व्योम cdns_mhdp_adjust_requested_cr(काष्ठा cdns_mhdp_device *mhdp,
					  u8 link_status[DP_LINK_STATUS_SIZE],
					  u8 *req_volt, u8 *req_pre)
अणु
	स्थिर u8 max_volt = CDNS_VOLT_SWING(mhdp->host.volt_swing);
	स्थिर u8 max_pre = CDNS_PRE_EMPHASIS(mhdp->host.pre_emphasis);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < mhdp->link.num_lanes; i++) अणु
		u8 val;

		val = mhdp->host.volt_swing & CDNS_FORCE_VOLT_SWING ?
		      max_volt : req_volt[i];
		cdns_mhdp_set_adjust_request_voltage(link_status, i, val);

		val = mhdp->host.pre_emphasis & CDNS_FORCE_PRE_EMPHASIS ?
		      max_pre : req_pre[i];
		cdns_mhdp_set_adjust_request_pre_emphasis(link_status, i, val);
	पूर्ण
पूर्ण

अटल
व्योम cdns_mhdp_validate_cr(काष्ठा cdns_mhdp_device *mhdp, bool *cr_करोne,
			   bool *same_beक्रमe_adjust, bool *max_swing_reached,
			   u8 beक्रमe_cr[CDNS_DP_MAX_NUM_LANES],
			   u8 after_cr[DP_LINK_STATUS_SIZE], u8 *req_volt,
			   u8 *req_pre)
अणु
	स्थिर u8 max_volt = CDNS_VOLT_SWING(mhdp->host.volt_swing);
	स्थिर u8 max_pre = CDNS_PRE_EMPHASIS(mhdp->host.pre_emphasis);
	bool same_pre, same_volt;
	अचिन्हित पूर्णांक i;
	u8 adjust;

	*same_beक्रमe_adjust = false;
	*max_swing_reached = false;
	*cr_करोne = drm_dp_घड़ी_recovery_ok(after_cr, mhdp->link.num_lanes);

	क्रम (i = 0; i < mhdp->link.num_lanes; i++) अणु
		adjust = drm_dp_get_adjust_request_voltage(after_cr, i);
		req_volt[i] = min(adjust, max_volt);

		adjust = drm_dp_get_adjust_request_pre_emphasis(after_cr, i) >>
		      DP_TRAIN_PRE_EMPHASIS_SHIFT;
		req_pre[i] = min(adjust, max_pre);

		same_pre = (beक्रमe_cr[i] & DP_TRAIN_PRE_EMPHASIS_MASK) ==
			   req_pre[i] << DP_TRAIN_PRE_EMPHASIS_SHIFT;
		same_volt = (beक्रमe_cr[i] & DP_TRAIN_VOLTAGE_SWING_MASK) ==
			    req_volt[i];
		अगर (same_pre && same_volt)
			*same_beक्रमe_adjust = true;

		/* 3.1.5.2 in DP Standard v1.4. Table 3-1 */
		अगर (!*cr_करोne && req_volt[i] + req_pre[i] >= 3) अणु
			*max_swing_reached = true;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool cdns_mhdp_link_training_cr(काष्ठा cdns_mhdp_device *mhdp)
अणु
	u8 lanes_data[CDNS_DP_MAX_NUM_LANES],
	fail_counter_लघु = 0, fail_counter_cr_दीर्घ = 0;
	u8 link_status[DP_LINK_STATUS_SIZE];
	bool cr_करोne;
	जोड़ phy_configure_opts phy_cfg;
	पूर्णांक ret;

	dev_dbg(mhdp->dev, "Starting CR phase\n");

	ret = cdns_mhdp_link_training_init(mhdp);
	अगर (ret)
		जाओ err;

	drm_dp_dpcd_पढ़ो_link_status(&mhdp->aux, link_status);

	करो अणु
		u8 requested_adjust_volt_swing[CDNS_DP_MAX_NUM_LANES] = अणुपूर्ण;
		u8 requested_adjust_pre_emphasis[CDNS_DP_MAX_NUM_LANES] = अणुपूर्ण;
		bool same_beक्रमe_adjust, max_swing_reached;

		cdns_mhdp_get_adjust_train(mhdp, link_status, lanes_data,
					   &phy_cfg);
		phy_cfg.dp.lanes = mhdp->link.num_lanes;
		phy_cfg.dp.ssc = cdns_mhdp_get_ssc_supported(mhdp);
		phy_cfg.dp.set_lanes = false;
		phy_cfg.dp.set_rate = false;
		phy_cfg.dp.set_voltages = true;
		ret = phy_configure(mhdp->phy,  &phy_cfg);
		अगर (ret) अणु
			dev_err(mhdp->dev, "%s: phy_configure() failed: %d\n",
				__func__, ret);
			जाओ err;
		पूर्ण

		cdns_mhdp_adjust_lt(mhdp, mhdp->link.num_lanes, 100,
				    lanes_data, link_status);

		cdns_mhdp_validate_cr(mhdp, &cr_करोne, &same_beक्रमe_adjust,
				      &max_swing_reached, lanes_data,
				      link_status,
				      requested_adjust_volt_swing,
				      requested_adjust_pre_emphasis);

		अगर (max_swing_reached) अणु
			dev_err(mhdp->dev, "CR: max swing reached\n");
			जाओ err;
		पूर्ण

		अगर (cr_करोne) अणु
			cdns_mhdp_prपूर्णांक_lt_status("CR phase ok", mhdp,
						  &phy_cfg);
			वापस true;
		पूर्ण

		/* Not all CR_DONE bits set */
		fail_counter_cr_दीर्घ++;

		अगर (same_beक्रमe_adjust) अणु
			fail_counter_लघु++;
			जारी;
		पूर्ण

		fail_counter_लघु = 0;
		/*
		 * Voltage swing/pre-emphasis adjust requested
		 * during CR phase
		 */
		cdns_mhdp_adjust_requested_cr(mhdp, link_status,
					      requested_adjust_volt_swing,
					      requested_adjust_pre_emphasis);
	पूर्ण जबतक (fail_counter_लघु < 5 && fail_counter_cr_दीर्घ < 10);

err:
	cdns_mhdp_prपूर्णांक_lt_status("CR phase failed", mhdp, &phy_cfg);

	वापस false;
पूर्ण

अटल व्योम cdns_mhdp_lower_link_rate(काष्ठा cdns_mhdp_link *link)
अणु
	चयन (drm_dp_link_rate_to_bw_code(link->rate)) अणु
	हाल DP_LINK_BW_2_7:
		link->rate = drm_dp_bw_code_to_link_rate(DP_LINK_BW_1_62);
		अवरोध;
	हाल DP_LINK_BW_5_4:
		link->rate = drm_dp_bw_code_to_link_rate(DP_LINK_BW_2_7);
		अवरोध;
	हाल DP_LINK_BW_8_1:
		link->rate = drm_dp_bw_code_to_link_rate(DP_LINK_BW_5_4);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक cdns_mhdp_link_training(काष्ठा cdns_mhdp_device *mhdp,
				   अचिन्हित पूर्णांक training_पूर्णांकerval)
अणु
	u32 reg32;
	स्थिर u8 eq_tps = cdns_mhdp_eq_training_pattern_supported(mhdp);
	पूर्णांक ret;

	जबतक (1) अणु
		अगर (!cdns_mhdp_link_training_cr(mhdp)) अणु
			अगर (drm_dp_link_rate_to_bw_code(mhdp->link.rate) !=
			    DP_LINK_BW_1_62) अणु
				dev_dbg(mhdp->dev,
					"Reducing link rate during CR phase\n");
				cdns_mhdp_lower_link_rate(&mhdp->link);

				जारी;
			पूर्ण अन्यथा अगर (mhdp->link.num_lanes > 1) अणु
				dev_dbg(mhdp->dev,
					"Reducing lanes number during CR phase\n");
				mhdp->link.num_lanes >>= 1;
				mhdp->link.rate = cdns_mhdp_max_link_rate(mhdp);

				जारी;
			पूर्ण

			dev_err(mhdp->dev,
				"Link training failed during CR phase\n");
			जाओ err;
		पूर्ण

		अगर (cdns_mhdp_link_training_channel_eq(mhdp, eq_tps,
						       training_पूर्णांकerval))
			अवरोध;

		अगर (mhdp->link.num_lanes > 1) अणु
			dev_dbg(mhdp->dev,
				"Reducing lanes number during EQ phase\n");
			mhdp->link.num_lanes >>= 1;

			जारी;
		पूर्ण अन्यथा अगर (drm_dp_link_rate_to_bw_code(mhdp->link.rate) !=
			   DP_LINK_BW_1_62) अणु
			dev_dbg(mhdp->dev,
				"Reducing link rate during EQ phase\n");
			cdns_mhdp_lower_link_rate(&mhdp->link);
			mhdp->link.num_lanes = cdns_mhdp_max_num_lanes(mhdp);

			जारी;
		पूर्ण

		dev_err(mhdp->dev, "Link training failed during EQ phase\n");
		जाओ err;
	पूर्ण

	dev_dbg(mhdp->dev, "Link training ok. Lanes: %u, Rate %u Mbps\n",
		mhdp->link.num_lanes, mhdp->link.rate / 100);

	drm_dp_dpcd_ग_लिखोb(&mhdp->aux, DP_TRAINING_PATTERN_SET,
			   mhdp->host.scrambler ? 0 :
			   DP_LINK_SCRAMBLING_DISABLE);

	ret = cdns_mhdp_reg_पढ़ो(mhdp, CDNS_DP_FRAMER_GLOBAL_CONFIG, &reg32);
	अगर (ret < 0) अणु
		dev_err(mhdp->dev,
			"Failed to read CDNS_DP_FRAMER_GLOBAL_CONFIG %d\n",
			ret);
		वापस ret;
	पूर्ण
	reg32 &= ~GENMASK(1, 0);
	reg32 |= CDNS_DP_NUM_LANES(mhdp->link.num_lanes);
	reg32 |= CDNS_DP_WR_FAILING_EDGE_VSYNC;
	reg32 |= CDNS_DP_FRAMER_EN;
	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_FRAMER_GLOBAL_CONFIG, reg32);

	/* Reset PHY config */
	reg32 = CDNS_PHY_COMMON_CONFIG | CDNS_PHY_TRAINING_TYPE(1);
	अगर (!mhdp->host.scrambler)
		reg32 |= CDNS_PHY_SCRAMBLER_BYPASS;
	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DPTX_PHY_CONFIG, reg32);

	वापस 0;
err:
	/* Reset PHY config */
	reg32 = CDNS_PHY_COMMON_CONFIG | CDNS_PHY_TRAINING_TYPE(1);
	अगर (!mhdp->host.scrambler)
		reg32 |= CDNS_PHY_SCRAMBLER_BYPASS;
	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DPTX_PHY_CONFIG, reg32);

	drm_dp_dpcd_ग_लिखोb(&mhdp->aux, DP_TRAINING_PATTERN_SET,
			   DP_TRAINING_PATTERN_DISABLE);

	वापस -EIO;
पूर्ण

अटल u32 cdns_mhdp_get_training_पूर्णांकerval_us(काष्ठा cdns_mhdp_device *mhdp,
					      u32 पूर्णांकerval)
अणु
	अगर (पूर्णांकerval == 0)
		वापस 400;
	अगर (पूर्णांकerval < 5)
		वापस 4000 << (पूर्णांकerval - 1);
	dev_err(mhdp->dev,
		"wrong training interval returned by DPCD: %d\n", पूर्णांकerval);
	वापस 0;
पूर्ण

अटल व्योम cdns_mhdp_fill_host_caps(काष्ठा cdns_mhdp_device *mhdp)
अणु
	अचिन्हित पूर्णांक link_rate;

	/* Get source capabilities based on PHY attributes */

	mhdp->host.lanes_cnt = mhdp->phy->attrs.bus_width;
	अगर (!mhdp->host.lanes_cnt)
		mhdp->host.lanes_cnt = 4;

	link_rate = mhdp->phy->attrs.max_link_rate;
	अगर (!link_rate)
		link_rate = drm_dp_bw_code_to_link_rate(DP_LINK_BW_8_1);
	अन्यथा
		/* PHY uses Mb/s, DRM uses tens of kb/s. */
		link_rate *= 100;

	mhdp->host.link_rate = link_rate;
	mhdp->host.volt_swing = CDNS_VOLT_SWING(3);
	mhdp->host.pre_emphasis = CDNS_PRE_EMPHASIS(3);
	mhdp->host.pattern_supp = CDNS_SUPPORT_TPS(1) |
				  CDNS_SUPPORT_TPS(2) | CDNS_SUPPORT_TPS(3) |
				  CDNS_SUPPORT_TPS(4);
	mhdp->host.lane_mapping = CDNS_LANE_MAPPING_NORMAL;
	mhdp->host.fast_link = false;
	mhdp->host.enhanced = true;
	mhdp->host.scrambler = true;
	mhdp->host.ssc = false;
पूर्ण

अटल व्योम cdns_mhdp_fill_sink_caps(काष्ठा cdns_mhdp_device *mhdp,
				     u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	mhdp->sink.link_rate = mhdp->link.rate;
	mhdp->sink.lanes_cnt = mhdp->link.num_lanes;
	mhdp->sink.enhanced = !!(mhdp->link.capabilities &
				 DP_LINK_CAP_ENHANCED_FRAMING);

	/* Set SSC support */
	mhdp->sink.ssc = !!(dpcd[DP_MAX_DOWNSPREAD] &
				  DP_MAX_DOWNSPREAD_0_5);

	/* Set TPS support */
	mhdp->sink.pattern_supp = CDNS_SUPPORT_TPS(1) | CDNS_SUPPORT_TPS(2);
	अगर (drm_dp_tps3_supported(dpcd))
		mhdp->sink.pattern_supp |= CDNS_SUPPORT_TPS(3);
	अगर (drm_dp_tps4_supported(dpcd))
		mhdp->sink.pattern_supp |= CDNS_SUPPORT_TPS(4);

	/* Set fast link support */
	mhdp->sink.fast_link = !!(dpcd[DP_MAX_DOWNSPREAD] &
				  DP_NO_AUX_HANDSHAKE_LINK_TRAINING);
पूर्ण

अटल पूर्णांक cdns_mhdp_link_up(काष्ठा cdns_mhdp_device *mhdp)
अणु
	u8 dpcd[DP_RECEIVER_CAP_SIZE], amp[2];
	u32 resp, पूर्णांकerval, पूर्णांकerval_us;
	u8 ext_cap_chk = 0;
	अचिन्हित पूर्णांक addr;
	पूर्णांक err;

	WARN_ON(!mutex_is_locked(&mhdp->link_mutex));

	drm_dp_dpcd_पढ़ोb(&mhdp->aux, DP_TRAINING_AUX_RD_INTERVAL,
			  &ext_cap_chk);

	अगर (ext_cap_chk & DP_EXTENDED_RECEIVER_CAP_FIELD_PRESENT)
		addr = DP_DP13_DPCD_REV;
	अन्यथा
		addr = DP_DPCD_REV;

	err = drm_dp_dpcd_पढ़ो(&mhdp->aux, addr, dpcd, DP_RECEIVER_CAP_SIZE);
	अगर (err < 0) अणु
		dev_err(mhdp->dev, "Failed to read receiver capabilities\n");
		वापस err;
	पूर्ण

	mhdp->link.revision = dpcd[0];
	mhdp->link.rate = drm_dp_bw_code_to_link_rate(dpcd[1]);
	mhdp->link.num_lanes = dpcd[2] & DP_MAX_LANE_COUNT_MASK;

	अगर (dpcd[2] & DP_ENHANCED_FRAME_CAP)
		mhdp->link.capabilities |= DP_LINK_CAP_ENHANCED_FRAMING;

	dev_dbg(mhdp->dev, "Set sink device power state via DPCD\n");
	cdns_mhdp_link_घातer_up(&mhdp->aux, &mhdp->link);

	cdns_mhdp_fill_sink_caps(mhdp, dpcd);

	mhdp->link.rate = cdns_mhdp_max_link_rate(mhdp);
	mhdp->link.num_lanes = cdns_mhdp_max_num_lanes(mhdp);

	/* Disable framer क्रम link training */
	err = cdns_mhdp_reg_पढ़ो(mhdp, CDNS_DP_FRAMER_GLOBAL_CONFIG, &resp);
	अगर (err < 0) अणु
		dev_err(mhdp->dev,
			"Failed to read CDNS_DP_FRAMER_GLOBAL_CONFIG %d\n",
			err);
		वापस err;
	पूर्ण

	resp &= ~CDNS_DP_FRAMER_EN;
	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_FRAMER_GLOBAL_CONFIG, resp);

	/* Spपढ़ो AMP अगर required, enable 8b/10b coding */
	amp[0] = cdns_mhdp_get_ssc_supported(mhdp) ? DP_SPREAD_AMP_0_5 : 0;
	amp[1] = DP_SET_ANSI_8B10B;
	drm_dp_dpcd_ग_लिखो(&mhdp->aux, DP_DOWNSPREAD_CTRL, amp, 2);

	अगर (mhdp->host.fast_link & mhdp->sink.fast_link) अणु
		dev_err(mhdp->dev, "fastlink not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	पूर्णांकerval = dpcd[DP_TRAINING_AUX_RD_INTERVAL] & DP_TRAINING_AUX_RD_MASK;
	पूर्णांकerval_us = cdns_mhdp_get_training_पूर्णांकerval_us(mhdp, पूर्णांकerval);
	अगर (!पूर्णांकerval_us ||
	    cdns_mhdp_link_training(mhdp, पूर्णांकerval_us)) अणु
		dev_err(mhdp->dev, "Link training failed. Exiting.\n");
		वापस -EIO;
	पूर्ण

	mhdp->link_up = true;

	वापस 0;
पूर्ण

अटल व्योम cdns_mhdp_link_करोwn(काष्ठा cdns_mhdp_device *mhdp)
अणु
	WARN_ON(!mutex_is_locked(&mhdp->link_mutex));

	अगर (mhdp->plugged)
		cdns_mhdp_link_घातer_करोwn(&mhdp->aux, &mhdp->link);

	mhdp->link_up = false;
पूर्ण

अटल काष्ठा edid *cdns_mhdp_get_edid(काष्ठा cdns_mhdp_device *mhdp,
				       काष्ठा drm_connector *connector)
अणु
	अगर (!mhdp->plugged)
		वापस शून्य;

	वापस drm_करो_get_edid(connector, cdns_mhdp_get_edid_block, mhdp);
पूर्ण

अटल पूर्णांक cdns_mhdp_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा cdns_mhdp_device *mhdp = connector_to_mhdp(connector);
	काष्ठा edid *edid;
	पूर्णांक num_modes;

	अगर (!mhdp->plugged)
		वापस 0;

	edid = cdns_mhdp_get_edid(mhdp, connector);
	अगर (!edid) अणु
		dev_err(mhdp->dev, "Failed to read EDID\n");
		वापस 0;
	पूर्ण

	drm_connector_update_edid_property(connector, edid);
	num_modes = drm_add_edid_modes(connector, edid);
	kमुक्त(edid);

	/*
	 * HACK: Warn about unsupported display क्रमmats until we deal
	 *       with them correctly.
	 */
	अगर (connector->display_info.color_क्रमmats &&
	    !(connector->display_info.color_क्रमmats &
	      mhdp->display_fmt.color_क्रमmat))
		dev_warn(mhdp->dev,
			 "%s: No supported color_format found (0x%08x)\n",
			__func__, connector->display_info.color_क्रमmats);

	अगर (connector->display_info.bpc &&
	    connector->display_info.bpc < mhdp->display_fmt.bpc)
		dev_warn(mhdp->dev, "%s: Display bpc only %d < %d\n",
			 __func__, connector->display_info.bpc,
			 mhdp->display_fmt.bpc);

	वापस num_modes;
पूर्ण

अटल पूर्णांक cdns_mhdp_connector_detect(काष्ठा drm_connector *conn,
				      काष्ठा drm_modeset_acquire_ctx *ctx,
				      bool क्रमce)
अणु
	काष्ठा cdns_mhdp_device *mhdp = connector_to_mhdp(conn);

	वापस cdns_mhdp_detect(mhdp);
पूर्ण

अटल u32 cdns_mhdp_get_bpp(काष्ठा cdns_mhdp_display_fmt *fmt)
अणु
	u32 bpp;

	अगर (fmt->y_only)
		वापस fmt->bpc;

	चयन (fmt->color_क्रमmat) अणु
	हाल DRM_COLOR_FORMAT_RGB444:
	हाल DRM_COLOR_FORMAT_YCRCB444:
		bpp = fmt->bpc * 3;
		अवरोध;
	हाल DRM_COLOR_FORMAT_YCRCB422:
		bpp = fmt->bpc * 2;
		अवरोध;
	हाल DRM_COLOR_FORMAT_YCRCB420:
		bpp = fmt->bpc * 3 / 2;
		अवरोध;
	शेष:
		bpp = fmt->bpc * 3;
		WARN_ON(1);
	पूर्ण
	वापस bpp;
पूर्ण

अटल
bool cdns_mhdp_bandwidth_ok(काष्ठा cdns_mhdp_device *mhdp,
			    स्थिर काष्ठा drm_display_mode *mode,
			    अचिन्हित पूर्णांक lanes, अचिन्हित पूर्णांक rate)
अणु
	u32 max_bw, req_bw, bpp;

	/*
	 * mode->घड़ी is expressed in kHz. Multiplying by bpp and भागiding by 8
	 * we get the number of kB/s. DisplayPort applies a 8b-10b encoding, the
	 * value thus equals the bandwidth in 10kb/s units, which matches the
	 * units of the rate parameter.
	 */

	bpp = cdns_mhdp_get_bpp(&mhdp->display_fmt);
	req_bw = mode->घड़ी * bpp / 8;
	max_bw = lanes * rate;
	अगर (req_bw > max_bw) अणु
		dev_dbg(mhdp->dev,
			"Unsupported Mode: %s, Req BW: %u, Available Max BW:%u\n",
			mode->name, req_bw, max_bw);

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल
क्रमागत drm_mode_status cdns_mhdp_mode_valid(काष्ठा drm_connector *conn,
					  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा cdns_mhdp_device *mhdp = connector_to_mhdp(conn);

	mutex_lock(&mhdp->link_mutex);

	अगर (!cdns_mhdp_bandwidth_ok(mhdp, mode, mhdp->link.num_lanes,
				    mhdp->link.rate)) अणु
		mutex_unlock(&mhdp->link_mutex);
		वापस MODE_CLOCK_HIGH;
	पूर्ण

	mutex_unlock(&mhdp->link_mutex);
	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs cdns_mhdp_conn_helper_funcs = अणु
	.detect_ctx = cdns_mhdp_connector_detect,
	.get_modes = cdns_mhdp_get_modes,
	.mode_valid = cdns_mhdp_mode_valid,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs cdns_mhdp_conn_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.reset = drm_atomic_helper_connector_reset,
	.destroy = drm_connector_cleanup,
पूर्ण;

अटल पूर्णांक cdns_mhdp_connector_init(काष्ठा cdns_mhdp_device *mhdp)
अणु
	u32 bus_क्रमmat = MEDIA_BUS_FMT_RGB121212_1X36;
	काष्ठा drm_connector *conn = &mhdp->connector;
	काष्ठा drm_bridge *bridge = &mhdp->bridge;
	पूर्णांक ret;

	अगर (!bridge->encoder) अणु
		dev_err(mhdp->dev, "Parent encoder object not found");
		वापस -ENODEV;
	पूर्ण

	conn->polled = DRM_CONNECTOR_POLL_HPD;

	ret = drm_connector_init(bridge->dev, conn, &cdns_mhdp_conn_funcs,
				 DRM_MODE_CONNECTOR_DisplayPort);
	अगर (ret) अणु
		dev_err(mhdp->dev, "Failed to initialize connector with drm\n");
		वापस ret;
	पूर्ण

	drm_connector_helper_add(conn, &cdns_mhdp_conn_helper_funcs);

	ret = drm_display_info_set_bus_क्रमmats(&conn->display_info,
					       &bus_क्रमmat, 1);
	अगर (ret)
		वापस ret;

	ret = drm_connector_attach_encoder(conn, bridge->encoder);
	अगर (ret) अणु
		dev_err(mhdp->dev, "Failed to attach connector to encoder\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_mhdp_attach(काष्ठा drm_bridge *bridge,
			    क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा cdns_mhdp_device *mhdp = bridge_to_mhdp(bridge);
	bool hw_पढ़ोy;
	पूर्णांक ret;

	dev_dbg(mhdp->dev, "%s\n", __func__);

	अगर (!(flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR)) अणु
		ret = cdns_mhdp_connector_init(mhdp);
		अगर (ret)
			वापस ret;
	पूर्ण

	spin_lock(&mhdp->start_lock);

	mhdp->bridge_attached = true;
	hw_पढ़ोy = mhdp->hw_state == MHDP_HW_READY;

	spin_unlock(&mhdp->start_lock);

	/* Enable SW event पूर्णांकerrupts */
	अगर (hw_पढ़ोy)
		ग_लिखोl(~(u32)CDNS_APB_INT_MASK_SW_EVENT_INT,
		       mhdp->regs + CDNS_APB_INT_MASK);

	वापस 0;
पूर्ण

अटल व्योम cdns_mhdp_configure_video(काष्ठा cdns_mhdp_device *mhdp,
				      स्थिर काष्ठा drm_display_mode *mode)
अणु
	अचिन्हित पूर्णांक dp_framer_sp = 0, msa_horizontal_1,
		msa_vertical_1, bnd_hsync2vsync, hsync2vsync_pol_ctrl,
		misc0 = 0, misc1 = 0, pxl_repr,
		front_porch, back_porch, msa_h0, msa_v0, hsync, vsync,
		dp_vertical_1;
	u8 stream_id = mhdp->stream_id;
	u32 bpp, bpc, pxlfmt, framer;
	पूर्णांक ret;

	pxlfmt = mhdp->display_fmt.color_क्रमmat;
	bpc = mhdp->display_fmt.bpc;

	/*
	 * If YCBCR supported and stream not SD, use ITU709
	 * Need to handle ITU version with YCBCR420 when supported
	 */
	अगर ((pxlfmt == DRM_COLOR_FORMAT_YCRCB444 ||
	     pxlfmt == DRM_COLOR_FORMAT_YCRCB422) && mode->crtc_vdisplay >= 720)
		misc0 = DP_YCBCR_COEFFICIENTS_ITU709;

	bpp = cdns_mhdp_get_bpp(&mhdp->display_fmt);

	चयन (pxlfmt) अणु
	हाल DRM_COLOR_FORMAT_RGB444:
		pxl_repr = CDNS_DP_FRAMER_RGB << CDNS_DP_FRAMER_PXL_FORMAT;
		misc0 |= DP_COLOR_FORMAT_RGB;
		अवरोध;
	हाल DRM_COLOR_FORMAT_YCRCB444:
		pxl_repr = CDNS_DP_FRAMER_YCBCR444 << CDNS_DP_FRAMER_PXL_FORMAT;
		misc0 |= DP_COLOR_FORMAT_YCbCr444 | DP_TEST_DYNAMIC_RANGE_CEA;
		अवरोध;
	हाल DRM_COLOR_FORMAT_YCRCB422:
		pxl_repr = CDNS_DP_FRAMER_YCBCR422 << CDNS_DP_FRAMER_PXL_FORMAT;
		misc0 |= DP_COLOR_FORMAT_YCbCr422 | DP_TEST_DYNAMIC_RANGE_CEA;
		अवरोध;
	हाल DRM_COLOR_FORMAT_YCRCB420:
		pxl_repr = CDNS_DP_FRAMER_YCBCR420 << CDNS_DP_FRAMER_PXL_FORMAT;
		अवरोध;
	शेष:
		pxl_repr = CDNS_DP_FRAMER_Y_ONLY << CDNS_DP_FRAMER_PXL_FORMAT;
	पूर्ण

	चयन (bpc) अणु
	हाल 6:
		misc0 |= DP_TEST_BIT_DEPTH_6;
		pxl_repr |= CDNS_DP_FRAMER_6_BPC;
		अवरोध;
	हाल 8:
		misc0 |= DP_TEST_BIT_DEPTH_8;
		pxl_repr |= CDNS_DP_FRAMER_8_BPC;
		अवरोध;
	हाल 10:
		misc0 |= DP_TEST_BIT_DEPTH_10;
		pxl_repr |= CDNS_DP_FRAMER_10_BPC;
		अवरोध;
	हाल 12:
		misc0 |= DP_TEST_BIT_DEPTH_12;
		pxl_repr |= CDNS_DP_FRAMER_12_BPC;
		अवरोध;
	हाल 16:
		misc0 |= DP_TEST_BIT_DEPTH_16;
		pxl_repr |= CDNS_DP_FRAMER_16_BPC;
		अवरोध;
	पूर्ण

	bnd_hsync2vsync = CDNS_IP_BYPASS_V_INTERFACE;
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		bnd_hsync2vsync |= CDNS_IP_DET_INTERLACE_FORMAT;

	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_BND_HSYNC2VSYNC(stream_id),
			    bnd_hsync2vsync);

	hsync2vsync_pol_ctrl = 0;
	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		hsync2vsync_pol_ctrl |= CDNS_H2V_HSYNC_POL_ACTIVE_LOW;
	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		hsync2vsync_pol_ctrl |= CDNS_H2V_VSYNC_POL_ACTIVE_LOW;
	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_HSYNC2VSYNC_POL_CTRL(stream_id),
			    hsync2vsync_pol_ctrl);

	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_FRAMER_PXL_REPR(stream_id), pxl_repr);

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		dp_framer_sp |= CDNS_DP_FRAMER_INTERLACE;
	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		dp_framer_sp |= CDNS_DP_FRAMER_HSYNC_POL_LOW;
	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		dp_framer_sp |= CDNS_DP_FRAMER_VSYNC_POL_LOW;
	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_FRAMER_SP(stream_id), dp_framer_sp);

	front_porch = mode->crtc_hsync_start - mode->crtc_hdisplay;
	back_porch = mode->crtc_htotal - mode->crtc_hsync_end;
	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_FRONT_BACK_PORCH(stream_id),
			    CDNS_DP_FRONT_PORCH(front_porch) |
			    CDNS_DP_BACK_PORCH(back_porch));

	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_BYTE_COUNT(stream_id),
			    mode->crtc_hdisplay * bpp / 8);

	msa_h0 = mode->crtc_htotal - mode->crtc_hsync_start;
	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_MSA_HORIZONTAL_0(stream_id),
			    CDNS_DP_MSAH0_H_TOTAL(mode->crtc_htotal) |
			    CDNS_DP_MSAH0_HSYNC_START(msa_h0));

	hsync = mode->crtc_hsync_end - mode->crtc_hsync_start;
	msa_horizontal_1 = CDNS_DP_MSAH1_HSYNC_WIDTH(hsync) |
			   CDNS_DP_MSAH1_HDISP_WIDTH(mode->crtc_hdisplay);
	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		msa_horizontal_1 |= CDNS_DP_MSAH1_HSYNC_POL_LOW;
	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_MSA_HORIZONTAL_1(stream_id),
			    msa_horizontal_1);

	msa_v0 = mode->crtc_vtotal - mode->crtc_vsync_start;
	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_MSA_VERTICAL_0(stream_id),
			    CDNS_DP_MSAV0_V_TOTAL(mode->crtc_vtotal) |
			    CDNS_DP_MSAV0_VSYNC_START(msa_v0));

	vsync = mode->crtc_vsync_end - mode->crtc_vsync_start;
	msa_vertical_1 = CDNS_DP_MSAV1_VSYNC_WIDTH(vsync) |
			 CDNS_DP_MSAV1_VDISP_WIDTH(mode->crtc_vdisplay);
	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		msa_vertical_1 |= CDNS_DP_MSAV1_VSYNC_POL_LOW;
	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_MSA_VERTICAL_1(stream_id),
			    msa_vertical_1);

	अगर ((mode->flags & DRM_MODE_FLAG_INTERLACE) &&
	    mode->crtc_vtotal % 2 == 0)
		misc1 = DP_TEST_INTERLACED;
	अगर (mhdp->display_fmt.y_only)
		misc1 |= CDNS_DP_TEST_COLOR_FORMAT_RAW_Y_ONLY;
	/* Use VSC SDP क्रम Y420 */
	अगर (pxlfmt == DRM_COLOR_FORMAT_YCRCB420)
		misc1 = CDNS_DP_TEST_VSC_SDP;

	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_MSA_MISC(stream_id),
			    misc0 | (misc1 << 8));

	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_HORIZONTAL(stream_id),
			    CDNS_DP_H_HSYNC_WIDTH(hsync) |
			    CDNS_DP_H_H_TOTAL(mode->crtc_hdisplay));

	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_VERTICAL_0(stream_id),
			    CDNS_DP_V0_VHEIGHT(mode->crtc_vdisplay) |
			    CDNS_DP_V0_VSTART(msa_v0));

	dp_vertical_1 = CDNS_DP_V1_VTOTAL(mode->crtc_vtotal);
	अगर ((mode->flags & DRM_MODE_FLAG_INTERLACE) &&
	    mode->crtc_vtotal % 2 == 0)
		dp_vertical_1 |= CDNS_DP_V1_VTOTAL_EVEN;

	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_VERTICAL_1(stream_id), dp_vertical_1);

	cdns_mhdp_reg_ग_लिखो_bit(mhdp, CDNS_DP_VB_ID(stream_id), 2, 1,
				(mode->flags & DRM_MODE_FLAG_INTERLACE) ?
				CDNS_DP_VB_ID_INTERLACED : 0);

	ret = cdns_mhdp_reg_पढ़ो(mhdp, CDNS_DP_FRAMER_GLOBAL_CONFIG, &framer);
	अगर (ret < 0) अणु
		dev_err(mhdp->dev,
			"Failed to read CDNS_DP_FRAMER_GLOBAL_CONFIG %d\n",
			ret);
		वापस;
	पूर्ण
	framer |= CDNS_DP_FRAMER_EN;
	framer &= ~CDNS_DP_NO_VIDEO_MODE;
	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_FRAMER_GLOBAL_CONFIG, framer);
पूर्ण

अटल व्योम cdns_mhdp_sst_enable(काष्ठा cdns_mhdp_device *mhdp,
				 स्थिर काष्ठा drm_display_mode *mode)
अणु
	u32 rate, vs, required_bandwidth, available_bandwidth;
	s32 line_thresh1, line_thresh2, line_thresh = 0;
	पूर्णांक pxlघड़ी = mode->crtc_घड़ी;
	u32 tu_size = 64;
	u32 bpp;

	/* Get rate in MSymbols per second per lane */
	rate = mhdp->link.rate / 1000;

	bpp = cdns_mhdp_get_bpp(&mhdp->display_fmt);

	required_bandwidth = pxlघड़ी * bpp / 8;
	available_bandwidth = mhdp->link.num_lanes * rate;

	vs = tu_size * required_bandwidth / available_bandwidth;
	vs /= 1000;

	अगर (vs == tu_size)
		vs = tu_size - 1;

	line_thresh1 = ((vs + 1) << 5) * 8 / bpp;
	line_thresh2 = (pxlघड़ी << 5) / 1000 / rate * (vs + 1) - (1 << 5);
	line_thresh = line_thresh1 - line_thresh2 / (s32)mhdp->link.num_lanes;
	line_thresh = (line_thresh >> 5) + 2;

	mhdp->stream_id = 0;

	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_FRAMER_TU,
			    CDNS_DP_FRAMER_TU_VS(vs) |
			    CDNS_DP_FRAMER_TU_SIZE(tu_size) |
			    CDNS_DP_FRAMER_TU_CNT_RST_EN);

	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_LINE_THRESH(0),
			    line_thresh & GENMASK(5, 0));

	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_STREAM_CONFIG_2(0),
			    CDNS_DP_SC2_TU_VS_DIFF((tu_size - vs > 3) ?
						   0 : tu_size - vs));

	cdns_mhdp_configure_video(mhdp, mode);
पूर्ण

अटल व्योम cdns_mhdp_atomic_enable(काष्ठा drm_bridge *bridge,
				    काष्ठा drm_bridge_state *bridge_state)
अणु
	काष्ठा cdns_mhdp_device *mhdp = bridge_to_mhdp(bridge);
	काष्ठा drm_atomic_state *state = bridge_state->base.state;
	काष्ठा cdns_mhdp_bridge_state *mhdp_state;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_bridge_state *new_state;
	स्थिर काष्ठा drm_display_mode *mode;
	u32 resp;
	पूर्णांक ret;

	dev_dbg(mhdp->dev, "bridge enable\n");

	mutex_lock(&mhdp->link_mutex);

	अगर (mhdp->plugged && !mhdp->link_up) अणु
		ret = cdns_mhdp_link_up(mhdp);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर (mhdp->info && mhdp->info->ops && mhdp->info->ops->enable)
		mhdp->info->ops->enable(mhdp);

	/* Enable VIF घड़ी क्रम stream 0 */
	ret = cdns_mhdp_reg_पढ़ो(mhdp, CDNS_DPTX_CAR, &resp);
	अगर (ret < 0) अणु
		dev_err(mhdp->dev, "Failed to read CDNS_DPTX_CAR %d\n", ret);
		जाओ out;
	पूर्ण

	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DPTX_CAR,
			    resp | CDNS_VIF_CLK_EN | CDNS_VIF_CLK_RSTN);

	connector = drm_atomic_get_new_connector_क्रम_encoder(state,
							     bridge->encoder);
	अगर (WARN_ON(!connector))
		जाओ out;

	conn_state = drm_atomic_get_new_connector_state(state, connector);
	अगर (WARN_ON(!conn_state))
		जाओ out;

	crtc_state = drm_atomic_get_new_crtc_state(state, conn_state->crtc);
	अगर (WARN_ON(!crtc_state))
		जाओ out;

	mode = &crtc_state->adjusted_mode;

	new_state = drm_atomic_get_new_bridge_state(state, bridge);
	अगर (WARN_ON(!new_state))
		जाओ out;

	अगर (!cdns_mhdp_bandwidth_ok(mhdp, mode, mhdp->link.num_lanes,
				    mhdp->link.rate)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	cdns_mhdp_sst_enable(mhdp, mode);

	mhdp_state = to_cdns_mhdp_bridge_state(new_state);

	mhdp_state->current_mode = drm_mode_duplicate(bridge->dev, mode);
	drm_mode_set_name(mhdp_state->current_mode);

	dev_dbg(mhdp->dev, "%s: Enabling mode %s\n", __func__, mode->name);

	mhdp->bridge_enabled = true;

out:
	mutex_unlock(&mhdp->link_mutex);
	अगर (ret < 0)
		schedule_work(&mhdp->modeset_retry_work);
पूर्ण

अटल व्योम cdns_mhdp_atomic_disable(काष्ठा drm_bridge *bridge,
				     काष्ठा drm_bridge_state *bridge_state)
अणु
	काष्ठा cdns_mhdp_device *mhdp = bridge_to_mhdp(bridge);
	u32 resp;

	dev_dbg(mhdp->dev, "%s\n", __func__);

	mutex_lock(&mhdp->link_mutex);

	mhdp->bridge_enabled = false;
	cdns_mhdp_reg_पढ़ो(mhdp, CDNS_DP_FRAMER_GLOBAL_CONFIG, &resp);
	resp &= ~CDNS_DP_FRAMER_EN;
	resp |= CDNS_DP_NO_VIDEO_MODE;
	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DP_FRAMER_GLOBAL_CONFIG, resp);

	cdns_mhdp_link_करोwn(mhdp);

	/* Disable VIF घड़ी क्रम stream 0 */
	cdns_mhdp_reg_पढ़ो(mhdp, CDNS_DPTX_CAR, &resp);
	cdns_mhdp_reg_ग_लिखो(mhdp, CDNS_DPTX_CAR,
			    resp & ~(CDNS_VIF_CLK_EN | CDNS_VIF_CLK_RSTN));

	अगर (mhdp->info && mhdp->info->ops && mhdp->info->ops->disable)
		mhdp->info->ops->disable(mhdp);

	mutex_unlock(&mhdp->link_mutex);
पूर्ण

अटल व्योम cdns_mhdp_detach(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा cdns_mhdp_device *mhdp = bridge_to_mhdp(bridge);

	dev_dbg(mhdp->dev, "%s\n", __func__);

	spin_lock(&mhdp->start_lock);

	mhdp->bridge_attached = false;

	spin_unlock(&mhdp->start_lock);

	ग_लिखोl(~0, mhdp->regs + CDNS_APB_INT_MASK);
पूर्ण

अटल काष्ठा drm_bridge_state *
cdns_mhdp_bridge_atomic_duplicate_state(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा cdns_mhdp_bridge_state *state;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_bridge_duplicate_state(bridge, &state->base);

	वापस &state->base;
पूर्ण

अटल व्योम
cdns_mhdp_bridge_atomic_destroy_state(काष्ठा drm_bridge *bridge,
				      काष्ठा drm_bridge_state *state)
अणु
	काष्ठा cdns_mhdp_bridge_state *cdns_mhdp_state;

	cdns_mhdp_state = to_cdns_mhdp_bridge_state(state);

	अगर (cdns_mhdp_state->current_mode) अणु
		drm_mode_destroy(bridge->dev, cdns_mhdp_state->current_mode);
		cdns_mhdp_state->current_mode = शून्य;
	पूर्ण

	kमुक्त(cdns_mhdp_state);
पूर्ण

अटल काष्ठा drm_bridge_state *
cdns_mhdp_bridge_atomic_reset(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा cdns_mhdp_bridge_state *cdns_mhdp_state;

	cdns_mhdp_state = kzalloc(माप(*cdns_mhdp_state), GFP_KERNEL);
	अगर (!cdns_mhdp_state)
		वापस शून्य;

	 __drm_atomic_helper_bridge_reset(bridge, &cdns_mhdp_state->base);

	वापस &cdns_mhdp_state->base;
पूर्ण

अटल पूर्णांक cdns_mhdp_atomic_check(काष्ठा drm_bridge *bridge,
				  काष्ठा drm_bridge_state *bridge_state,
				  काष्ठा drm_crtc_state *crtc_state,
				  काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा cdns_mhdp_device *mhdp = bridge_to_mhdp(bridge);
	स्थिर काष्ठा drm_display_mode *mode = &crtc_state->adjusted_mode;

	mutex_lock(&mhdp->link_mutex);

	अगर (!cdns_mhdp_bandwidth_ok(mhdp, mode, mhdp->link.num_lanes,
				    mhdp->link.rate)) अणु
		dev_err(mhdp->dev, "%s: Not enough BW for %s (%u lanes at %u Mbps)\n",
			__func__, mode->name, mhdp->link.num_lanes,
			mhdp->link.rate / 100);
		mutex_unlock(&mhdp->link_mutex);
		वापस -EINVAL;
	पूर्ण

	mutex_unlock(&mhdp->link_mutex);
	वापस 0;
पूर्ण

अटल क्रमागत drm_connector_status cdns_mhdp_bridge_detect(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा cdns_mhdp_device *mhdp = bridge_to_mhdp(bridge);

	वापस cdns_mhdp_detect(mhdp);
पूर्ण

अटल काष्ठा edid *cdns_mhdp_bridge_get_edid(काष्ठा drm_bridge *bridge,
					      काष्ठा drm_connector *connector)
अणु
	काष्ठा cdns_mhdp_device *mhdp = bridge_to_mhdp(bridge);

	वापस cdns_mhdp_get_edid(mhdp, connector);
पूर्ण

अटल व्योम cdns_mhdp_bridge_hpd_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा cdns_mhdp_device *mhdp = bridge_to_mhdp(bridge);

	/* Enable SW event पूर्णांकerrupts */
	अगर (mhdp->bridge_attached)
		ग_लिखोl(~(u32)CDNS_APB_INT_MASK_SW_EVENT_INT,
		       mhdp->regs + CDNS_APB_INT_MASK);
पूर्ण

अटल व्योम cdns_mhdp_bridge_hpd_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा cdns_mhdp_device *mhdp = bridge_to_mhdp(bridge);

	ग_लिखोl(CDNS_APB_INT_MASK_SW_EVENT_INT, mhdp->regs + CDNS_APB_INT_MASK);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs cdns_mhdp_bridge_funcs = अणु
	.atomic_enable = cdns_mhdp_atomic_enable,
	.atomic_disable = cdns_mhdp_atomic_disable,
	.atomic_check = cdns_mhdp_atomic_check,
	.attach = cdns_mhdp_attach,
	.detach = cdns_mhdp_detach,
	.atomic_duplicate_state = cdns_mhdp_bridge_atomic_duplicate_state,
	.atomic_destroy_state = cdns_mhdp_bridge_atomic_destroy_state,
	.atomic_reset = cdns_mhdp_bridge_atomic_reset,
	.detect = cdns_mhdp_bridge_detect,
	.get_edid = cdns_mhdp_bridge_get_edid,
	.hpd_enable = cdns_mhdp_bridge_hpd_enable,
	.hpd_disable = cdns_mhdp_bridge_hpd_disable,
पूर्ण;

अटल bool cdns_mhdp_detect_hpd(काष्ठा cdns_mhdp_device *mhdp, bool *hpd_pulse)
अणु
	पूर्णांक hpd_event, hpd_status;

	*hpd_pulse = false;

	hpd_event = cdns_mhdp_पढ़ो_hpd_event(mhdp);

	/* Getting event bits failed, bail out */
	अगर (hpd_event < 0) अणु
		dev_warn(mhdp->dev, "%s: read event failed: %d\n",
			 __func__, hpd_event);
		वापस false;
	पूर्ण

	hpd_status = cdns_mhdp_get_hpd_status(mhdp);
	अगर (hpd_status < 0) अणु
		dev_warn(mhdp->dev, "%s: get hpd status failed: %d\n",
			 __func__, hpd_status);
		वापस false;
	पूर्ण

	अगर (hpd_event & DPTX_READ_EVENT_HPD_PULSE)
		*hpd_pulse = true;

	वापस !!hpd_status;
पूर्ण

अटल पूर्णांक cdns_mhdp_update_link_status(काष्ठा cdns_mhdp_device *mhdp)
अणु
	काष्ठा cdns_mhdp_bridge_state *cdns_bridge_state;
	काष्ठा drm_display_mode *current_mode;
	bool old_plugged = mhdp->plugged;
	काष्ठा drm_bridge_state *state;
	u8 status[DP_LINK_STATUS_SIZE];
	bool hpd_pulse;
	पूर्णांक ret = 0;

	mutex_lock(&mhdp->link_mutex);

	mhdp->plugged = cdns_mhdp_detect_hpd(mhdp, &hpd_pulse);

	अगर (!mhdp->plugged) अणु
		cdns_mhdp_link_करोwn(mhdp);
		mhdp->link.rate = mhdp->host.link_rate;
		mhdp->link.num_lanes = mhdp->host.lanes_cnt;
		जाओ out;
	पूर्ण

	/*
	 * If we get a HPD pulse event and we were and still are connected,
	 * check the link status. If link status is ok, there's nothing to करो
	 * as we करोn't handle DP पूर्णांकerrupts. If link status is bad, जारी
	 * with full link setup.
	 */
	अगर (hpd_pulse && old_plugged == mhdp->plugged) अणु
		ret = drm_dp_dpcd_पढ़ो_link_status(&mhdp->aux, status);

		/*
		 * If everything looks fine, just वापस, as we करोn't handle
		 * DP IRQs.
		 */
		अगर (ret > 0 &&
		    drm_dp_channel_eq_ok(status, mhdp->link.num_lanes) &&
		    drm_dp_घड़ी_recovery_ok(status, mhdp->link.num_lanes))
			जाओ out;

		/* If link is bad, mark link as करोwn so that we करो a new LT */
		mhdp->link_up = false;
	पूर्ण

	अगर (!mhdp->link_up) अणु
		ret = cdns_mhdp_link_up(mhdp);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर (mhdp->bridge_enabled) अणु
		state = drm_priv_to_bridge_state(mhdp->bridge.base.state);
		अगर (!state) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		cdns_bridge_state = to_cdns_mhdp_bridge_state(state);
		अगर (!cdns_bridge_state) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		current_mode = cdns_bridge_state->current_mode;
		अगर (!current_mode) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (!cdns_mhdp_bandwidth_ok(mhdp, current_mode, mhdp->link.num_lanes,
					    mhdp->link.rate)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		dev_dbg(mhdp->dev, "%s: Enabling mode %s\n", __func__,
			current_mode->name);

		cdns_mhdp_sst_enable(mhdp, current_mode);
	पूर्ण
out:
	mutex_unlock(&mhdp->link_mutex);
	वापस ret;
पूर्ण

अटल व्योम cdns_mhdp_modeset_retry_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cdns_mhdp_device *mhdp;
	काष्ठा drm_connector *conn;

	mhdp = container_of(work, typeof(*mhdp), modeset_retry_work);

	conn = &mhdp->connector;

	/* Grab the locks beक्रमe changing connector property */
	mutex_lock(&conn->dev->mode_config.mutex);

	/*
	 * Set connector link status to BAD and send a Uevent to notअगरy
	 * userspace to करो a modeset.
	 */
	drm_connector_set_link_status_property(conn, DRM_MODE_LINK_STATUS_BAD);
	mutex_unlock(&conn->dev->mode_config.mutex);

	/* Send Hotplug uevent so userspace can reprobe */
	drm_kms_helper_hotplug_event(mhdp->bridge.dev);
पूर्ण

अटल irqवापस_t cdns_mhdp_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cdns_mhdp_device *mhdp = data;
	u32 apb_stat, sw_ev0;
	bool bridge_attached;
	पूर्णांक ret;

	apb_stat = पढ़ोl(mhdp->regs + CDNS_APB_INT_STATUS);
	अगर (!(apb_stat & CDNS_APB_INT_MASK_SW_EVENT_INT))
		वापस IRQ_NONE;

	sw_ev0 = पढ़ोl(mhdp->regs + CDNS_SW_EVENT0);

	/*
	 *  Calling drm_kms_helper_hotplug_event() when not attached
	 *  to drm device causes an oops because the drm_bridge->dev
	 *  is शून्य. See cdns_mhdp_fw_cb() comments क्रम details about the
	 *  problems related drm_kms_helper_hotplug_event() call.
	 */
	spin_lock(&mhdp->start_lock);
	bridge_attached = mhdp->bridge_attached;
	spin_unlock(&mhdp->start_lock);

	अगर (bridge_attached && (sw_ev0 & CDNS_DPTX_HPD)) अणु
		ret = cdns_mhdp_update_link_status(mhdp);
		अगर (mhdp->connector.dev) अणु
			अगर (ret < 0)
				schedule_work(&mhdp->modeset_retry_work);
			अन्यथा
				drm_kms_helper_hotplug_event(mhdp->bridge.dev);
		पूर्ण अन्यथा अणु
			drm_bridge_hpd_notअगरy(&mhdp->bridge, cdns_mhdp_detect(mhdp));
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cdns_mhdp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cdns_mhdp_device *mhdp;
	अचिन्हित दीर्घ rate;
	काष्ठा clk *clk;
	पूर्णांक ret;
	पूर्णांक irq;

	mhdp = devm_kzalloc(dev, माप(*mhdp), GFP_KERNEL);
	अगर (!mhdp)
		वापस -ENOMEM;

	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "couldn't get clk: %ld\n", PTR_ERR(clk));
		वापस PTR_ERR(clk);
	पूर्ण

	mhdp->clk = clk;
	mhdp->dev = dev;
	mutex_init(&mhdp->mbox_mutex);
	mutex_init(&mhdp->link_mutex);
	spin_lock_init(&mhdp->start_lock);

	drm_dp_aux_init(&mhdp->aux);
	mhdp->aux.dev = dev;
	mhdp->aux.transfer = cdns_mhdp_transfer;

	mhdp->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mhdp->regs)) अणु
		dev_err(dev, "Failed to get memory resource\n");
		वापस PTR_ERR(mhdp->regs);
	पूर्ण

	mhdp->phy = devm_of_phy_get_by_index(dev, pdev->dev.of_node, 0);
	अगर (IS_ERR(mhdp->phy)) अणु
		dev_err(dev, "no PHY configured\n");
		वापस PTR_ERR(mhdp->phy);
	पूर्ण

	platक्रमm_set_drvdata(pdev, mhdp);

	mhdp->info = of_device_get_match_data(dev);

	clk_prepare_enable(clk);

	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "pm_runtime_get_sync failed\n");
		pm_runसमय_disable(dev);
		जाओ clk_disable;
	पूर्ण

	अगर (mhdp->info && mhdp->info->ops && mhdp->info->ops->init) अणु
		ret = mhdp->info->ops->init(mhdp);
		अगर (ret != 0) अणु
			dev_err(dev, "MHDP platform initialization failed: %d\n",
				ret);
			जाओ runसमय_put;
		पूर्ण
	पूर्ण

	rate = clk_get_rate(clk);
	ग_लिखोl(rate % 1000000, mhdp->regs + CDNS_SW_CLK_L);
	ग_लिखोl(rate / 1000000, mhdp->regs + CDNS_SW_CLK_H);

	dev_dbg(dev, "func clk rate %lu Hz\n", rate);

	ग_लिखोl(~0, mhdp->regs + CDNS_APB_INT_MASK);

	irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_thपढ़ोed_irq(mhdp->dev, irq, शून्य,
					cdns_mhdp_irq_handler, IRQF_ONESHOT,
					"mhdp8546", mhdp);
	अगर (ret) अणु
		dev_err(dev, "cannot install IRQ %d\n", irq);
		ret = -EIO;
		जाओ plat_fini;
	पूर्ण

	cdns_mhdp_fill_host_caps(mhdp);

	/* Initialize link rate and num of lanes to host values */
	mhdp->link.rate = mhdp->host.link_rate;
	mhdp->link.num_lanes = mhdp->host.lanes_cnt;

	/* The only currently supported क्रमmat */
	mhdp->display_fmt.y_only = false;
	mhdp->display_fmt.color_क्रमmat = DRM_COLOR_FORMAT_RGB444;
	mhdp->display_fmt.bpc = 8;

	mhdp->bridge.of_node = pdev->dev.of_node;
	mhdp->bridge.funcs = &cdns_mhdp_bridge_funcs;
	mhdp->bridge.ops = DRM_BRIDGE_OP_DETECT | DRM_BRIDGE_OP_EDID |
			   DRM_BRIDGE_OP_HPD;
	mhdp->bridge.type = DRM_MODE_CONNECTOR_DisplayPort;
	अगर (mhdp->info)
		mhdp->bridge.timings = mhdp->info->timings;

	ret = phy_init(mhdp->phy);
	अगर (ret) अणु
		dev_err(mhdp->dev, "Failed to initialize PHY: %d\n", ret);
		जाओ plat_fini;
	पूर्ण

	/* Initialize the work क्रम modeset in हाल of link train failure */
	INIT_WORK(&mhdp->modeset_retry_work, cdns_mhdp_modeset_retry_fn);

	init_रुकोqueue_head(&mhdp->fw_load_wq);

	ret = cdns_mhdp_load_firmware(mhdp);
	अगर (ret)
		जाओ phy_निकास;

	drm_bridge_add(&mhdp->bridge);

	वापस 0;

phy_निकास:
	phy_निकास(mhdp->phy);
plat_fini:
	अगर (mhdp->info && mhdp->info->ops && mhdp->info->ops->निकास)
		mhdp->info->ops->निकास(mhdp);
runसमय_put:
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
clk_disable:
	clk_disable_unprepare(mhdp->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_mhdp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns_mhdp_device *mhdp = platक्रमm_get_drvdata(pdev);
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(100);
	bool stop_fw = false;
	पूर्णांक ret;

	drm_bridge_हटाओ(&mhdp->bridge);

	ret = रुको_event_समयout(mhdp->fw_load_wq,
				 mhdp->hw_state == MHDP_HW_READY,
				 समयout);
	अगर (ret == 0)
		dev_err(mhdp->dev, "%s: Timeout waiting for fw loading\n",
			__func__);
	अन्यथा
		stop_fw = true;

	spin_lock(&mhdp->start_lock);
	mhdp->hw_state = MHDP_HW_STOPPED;
	spin_unlock(&mhdp->start_lock);

	अगर (stop_fw)
		ret = cdns_mhdp_set_firmware_active(mhdp, false);

	phy_निकास(mhdp->phy);

	अगर (mhdp->info && mhdp->info->ops && mhdp->info->ops->निकास)
		mhdp->info->ops->निकास(mhdp);

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	cancel_work_sync(&mhdp->modeset_retry_work);
	flush_scheduled_work();

	clk_disable_unprepare(mhdp->clk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id mhdp_ids[] = अणु
	अणु .compatible = "cdns,mhdp8546", पूर्ण,
#अगर_घोषित CONFIG_DRM_CDNS_MHDP8546_J721E
	अणु .compatible = "ti,j721e-mhdp8546",
	  .data = &(स्थिर काष्ठा cdns_mhdp_platक्रमm_info) अणु
		  .timings = &mhdp_ti_j721e_bridge_timings,
		  .ops = &mhdp_ti_j721e_ops,
	  पूर्ण,
	पूर्ण,
#पूर्ण_अगर
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mhdp_ids);

अटल काष्ठा platक्रमm_driver mhdp_driver = अणु
	.driver	= अणु
		.name		= "cdns-mhdp8546",
		.of_match_table	= of_match_ptr(mhdp_ids),
	पूर्ण,
	.probe	= cdns_mhdp_probe,
	.हटाओ	= cdns_mhdp_हटाओ,
पूर्ण;
module_platक्रमm_driver(mhdp_driver);

MODULE_FIRMWARE(FW_NAME);

MODULE_AUTHOR("Quentin Schulz <quentin.schulz@free-electrons.com>");
MODULE_AUTHOR("Swapnil Jakhade <sjakhade@cadence.com>");
MODULE_AUTHOR("Yuti Amonkar <yamonkar@cadence.com>");
MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_AUTHOR("Jyri Sarha <jsarha@ti.com>");
MODULE_DESCRIPTION("Cadence MHDP8546 DP bridge driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:cdns-mhdp8546");
