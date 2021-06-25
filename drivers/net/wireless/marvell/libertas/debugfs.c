<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/dcache.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

#समावेश "decl.h"
#समावेश "cmd.h"
#समावेश "debugfs.h"

अटल काष्ठा dentry *lbs_dir;
अटल अक्षर *szStates[] = अणु
	"Connected",
	"Disconnected"
पूर्ण;

#अगर_घोषित PROC_DEBUG
अटल व्योम lbs_debug_init(काष्ठा lbs_निजी *priv);
#पूर्ण_अगर

अटल sमाप_प्रकार ग_लिखो_file_dummy(काष्ठा file *file, स्थिर अक्षर __user *buf,
                                माप_प्रकार count, loff_t *ppos)
अणु
        वापस -EINVAL;
पूर्ण

अटल स्थिर माप_प्रकार len = PAGE_SIZE;

अटल sमाप_प्रकार lbs_dev_info(काष्ठा file *file, अक्षर __user *userbuf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा lbs_निजी *priv = file->निजी_data;
	माप_प्रकार pos = 0;
	अचिन्हित दीर्घ addr = get_zeroed_page(GFP_KERNEL);
	अक्षर *buf = (अक्षर *)addr;
	sमाप_प्रकार res;
	अगर (!buf)
		वापस -ENOMEM;

	pos += snम_लिखो(buf+pos, len-pos, "state = %s\n",
				szStates[priv->connect_status]);
	pos += snम_लिखो(buf+pos, len-pos, "region_code = %02x\n",
				(u32) priv->regioncode);

	res = simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, pos);

	मुक्त_page(addr);
	वापस res;
पूर्ण

अटल sमाप_प्रकार lbs_sleepparams_ग_लिखो(काष्ठा file *file,
				स्थिर अक्षर __user *user_buf, माप_प्रकार count,
				loff_t *ppos)
अणु
	काष्ठा lbs_निजी *priv = file->निजी_data;
	sमाप_प्रकार ret;
	काष्ठा sleep_params sp;
	पूर्णांक p1, p2, p3, p4, p5, p6;
	अक्षर *buf;

	buf = memdup_user_nul(user_buf, min(count, len - 1));
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	ret = माला_पूछो(buf, "%d %d %d %d %d %d", &p1, &p2, &p3, &p4, &p5, &p6);
	अगर (ret != 6) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	sp.sp_error = p1;
	sp.sp_offset = p2;
	sp.sp_stableसमय = p3;
	sp.sp_calcontrol = p4;
	sp.sp_extsleepclk = p5;
	sp.sp_reserved = p6;

	ret = lbs_cmd_802_11_sleep_params(priv, CMD_ACT_SET, &sp);
	अगर (!ret)
		ret = count;
	अन्यथा अगर (ret > 0)
		ret = -EINVAL;

out_unlock:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार lbs_sleepparams_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा lbs_निजी *priv = file->निजी_data;
	sमाप_प्रकार ret;
	माप_प्रकार pos = 0;
	काष्ठा sleep_params sp;
	अचिन्हित दीर्घ addr = get_zeroed_page(GFP_KERNEL);
	अक्षर *buf = (अक्षर *)addr;
	अगर (!buf)
		वापस -ENOMEM;

	ret = lbs_cmd_802_11_sleep_params(priv, CMD_ACT_GET, &sp);
	अगर (ret)
		जाओ out_unlock;

	pos += snम_लिखो(buf, len, "%d %d %d %d %d %d\n", sp.sp_error,
			sp.sp_offset, sp.sp_stableसमय,
			sp.sp_calcontrol, sp.sp_extsleepclk,
			sp.sp_reserved);

	ret = simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, pos);

out_unlock:
	मुक्त_page(addr);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार lbs_host_sleep_ग_लिखो(काष्ठा file *file,
				स्थिर अक्षर __user *user_buf, माप_प्रकार count,
				loff_t *ppos)
अणु
	काष्ठा lbs_निजी *priv = file->निजी_data;
	sमाप_प्रकार ret;
	पूर्णांक host_sleep;
	अक्षर *buf;

	buf = memdup_user_nul(user_buf, min(count, len - 1));
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	ret = माला_पूछो(buf, "%d", &host_sleep);
	अगर (ret != 1) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (host_sleep == 0)
		ret = lbs_set_host_sleep(priv, 0);
	अन्यथा अगर (host_sleep == 1) अणु
		अगर (priv->wol_criteria == EHS_REMOVE_WAKEUP) अणु
			netdev_info(priv->dev,
				    "wake parameters not configured\n");
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		ret = lbs_set_host_sleep(priv, 1);
	पूर्ण अन्यथा अणु
		netdev_err(priv->dev, "invalid option\n");
		ret = -EINVAL;
	पूर्ण

	अगर (!ret)
		ret = count;

out_unlock:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार lbs_host_sleep_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा lbs_निजी *priv = file->निजी_data;
	sमाप_प्रकार ret;
	माप_प्रकार pos = 0;
	अचिन्हित दीर्घ addr = get_zeroed_page(GFP_KERNEL);
	अक्षर *buf = (अक्षर *)addr;
	अगर (!buf)
		वापस -ENOMEM;

	pos += snम_लिखो(buf, len, "%d\n", priv->is_host_sleep_activated);

	ret = simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, pos);

	मुक्त_page(addr);
	वापस ret;
पूर्ण

/*
 * When calling CMD_802_11_SUBSCRIBE_EVENT with CMD_ACT_GET, me might
 * get a bunch of venकरोr-specअगरic TLVs (a.k.a. IEs) back from the
 * firmware. Here's an example:
 *	04 01 02 00 00 00 05 01 02 00 00 00 06 01 02 00
 *	00 00 07 01 02 00 3c 00 00 00 00 00 00 00 03 03
 *	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
 *
 * The 04 01 is the TLV type (here TLV_TYPE_RSSI_LOW), 02 00 is the length,
 * 00 00 are the data bytes of this TLV. For this TLV, their meaning is
 * defined in mrvlietypes_thresholds
 *
 * This function searches in this TLV data chunk क्रम a given TLV type
 * and वापसs a poपूर्णांकer to the first data byte of the TLV, or to शून्य
 * अगर the TLV hasn't been found.
 */
अटल व्योम *lbs_tlv_find(uपूर्णांक16_t tlv_type, स्थिर uपूर्णांक8_t *tlv, uपूर्णांक16_t size)
अणु
	काष्ठा mrvl_ie_header *tlv_h;
	uपूर्णांक16_t length;
	sमाप_प्रकार pos = 0;

	जबतक (pos < size) अणु
		tlv_h = (काष्ठा mrvl_ie_header *) tlv;
		अगर (!tlv_h->len)
			वापस शून्य;
		अगर (tlv_h->type == cpu_to_le16(tlv_type))
			वापस tlv_h;
		length = le16_to_cpu(tlv_h->len) + माप(*tlv_h);
		pos += length;
		tlv += length;
	पूर्ण
	वापस शून्य;
पूर्ण


अटल sमाप_प्रकार lbs_threshold_पढ़ो(uपूर्णांक16_t tlv_type, uपूर्णांक16_t event_mask,
				  काष्ठा file *file, अक्षर __user *userbuf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा cmd_ds_802_11_subscribe_event *subscribed;
	काष्ठा mrvl_ie_thresholds *got;
	काष्ठा lbs_निजी *priv = file->निजी_data;
	sमाप_प्रकार ret = 0;
	माप_प्रकार pos = 0;
	अक्षर *buf;
	u8 value;
	u8 freq;
	पूर्णांक events = 0;

	buf = (अक्षर *)get_zeroed_page(GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	subscribed = kzalloc(माप(*subscribed), GFP_KERNEL);
	अगर (!subscribed) अणु
		ret = -ENOMEM;
		जाओ out_page;
	पूर्ण

	subscribed->hdr.size = cpu_to_le16(माप(*subscribed));
	subscribed->action = cpu_to_le16(CMD_ACT_GET);

	ret = lbs_cmd_with_response(priv, CMD_802_11_SUBSCRIBE_EVENT, subscribed);
	अगर (ret)
		जाओ out_cmd;

	got = lbs_tlv_find(tlv_type, subscribed->tlv, माप(subscribed->tlv));
	अगर (got) अणु
		value = got->value;
		freq  = got->freq;
		events = le16_to_cpu(subscribed->events);

		pos += snम_लिखो(buf, len, "%d %d %d\n", value, freq,
				!!(events & event_mask));
	पूर्ण

	ret = simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, pos);

 out_cmd:
	kमुक्त(subscribed);

 out_page:
	मुक्त_page((अचिन्हित दीर्घ)buf);
	वापस ret;
पूर्ण


अटल sमाप_प्रकार lbs_threshold_ग_लिखो(uपूर्णांक16_t tlv_type, uपूर्णांक16_t event_mask,
				   काष्ठा file *file,
				   स्थिर अक्षर __user *userbuf, माप_प्रकार count,
				   loff_t *ppos)
अणु
	काष्ठा cmd_ds_802_11_subscribe_event *events;
	काष्ठा mrvl_ie_thresholds *tlv;
	काष्ठा lbs_निजी *priv = file->निजी_data;
	पूर्णांक value, freq, new_mask;
	uपूर्णांक16_t curr_mask;
	अक्षर *buf;
	पूर्णांक ret;

	buf = memdup_user_nul(userbuf, min(count, len - 1));
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	ret = माला_पूछो(buf, "%d %d %d", &value, &freq, &new_mask);
	अगर (ret != 3) अणु
		ret = -EINVAL;
		जाओ out_page;
	पूर्ण
	events = kzalloc(माप(*events), GFP_KERNEL);
	अगर (!events) अणु
		ret = -ENOMEM;
		जाओ out_page;
	पूर्ण

	events->hdr.size = cpu_to_le16(माप(*events));
	events->action = cpu_to_le16(CMD_ACT_GET);

	ret = lbs_cmd_with_response(priv, CMD_802_11_SUBSCRIBE_EVENT, events);
	अगर (ret)
		जाओ out_events;

	curr_mask = le16_to_cpu(events->events);

	अगर (new_mask)
		new_mask = curr_mask | event_mask;
	अन्यथा
		new_mask = curr_mask & ~event_mask;

	/* Now everything is set and we can send stuff करोwn to the firmware */

	tlv = (व्योम *)events->tlv;

	events->action = cpu_to_le16(CMD_ACT_SET);
	events->events = cpu_to_le16(new_mask);
	tlv->header.type = cpu_to_le16(tlv_type);
	tlv->header.len = cpu_to_le16(माप(*tlv) - माप(tlv->header));
	tlv->value = value;
	अगर (tlv_type != TLV_TYPE_BCNMISS)
		tlv->freq = freq;

	/* The command header, the action, the event mask, and one TLV */
	events->hdr.size = cpu_to_le16(माप(events->hdr) + 4 + माप(*tlv));

	ret = lbs_cmd_with_response(priv, CMD_802_11_SUBSCRIBE_EVENT, events);

	अगर (!ret)
		ret = count;
 out_events:
	kमुक्त(events);
 out_page:
	kमुक्त(buf);
	वापस ret;
पूर्ण


अटल sमाप_प्रकार lbs_lowrssi_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	वापस lbs_threshold_पढ़ो(TLV_TYPE_RSSI_LOW, CMD_SUBSCRIBE_RSSI_LOW,
				  file, userbuf, count, ppos);
पूर्ण


अटल sमाप_प्रकार lbs_lowrssi_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	वापस lbs_threshold_ग_लिखो(TLV_TYPE_RSSI_LOW, CMD_SUBSCRIBE_RSSI_LOW,
				   file, userbuf, count, ppos);
पूर्ण


अटल sमाप_प्रकार lbs_lowsnr_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	वापस lbs_threshold_पढ़ो(TLV_TYPE_SNR_LOW, CMD_SUBSCRIBE_SNR_LOW,
				  file, userbuf, count, ppos);
पूर्ण


अटल sमाप_प्रकार lbs_lowsnr_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *userbuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	वापस lbs_threshold_ग_लिखो(TLV_TYPE_SNR_LOW, CMD_SUBSCRIBE_SNR_LOW,
				   file, userbuf, count, ppos);
पूर्ण


अटल sमाप_प्रकार lbs_failcount_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	वापस lbs_threshold_पढ़ो(TLV_TYPE_FAILCOUNT, CMD_SUBSCRIBE_FAILCOUNT,
				  file, userbuf, count, ppos);
पूर्ण


अटल sमाप_प्रकार lbs_failcount_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *userbuf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	वापस lbs_threshold_ग_लिखो(TLV_TYPE_FAILCOUNT, CMD_SUBSCRIBE_FAILCOUNT,
				   file, userbuf, count, ppos);
पूर्ण


अटल sमाप_प्रकार lbs_highrssi_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	वापस lbs_threshold_पढ़ो(TLV_TYPE_RSSI_HIGH, CMD_SUBSCRIBE_RSSI_HIGH,
				  file, userbuf, count, ppos);
पूर्ण


अटल sमाप_प्रकार lbs_highrssi_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *userbuf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	वापस lbs_threshold_ग_लिखो(TLV_TYPE_RSSI_HIGH, CMD_SUBSCRIBE_RSSI_HIGH,
				   file, userbuf, count, ppos);
पूर्ण


अटल sमाप_प्रकार lbs_highsnr_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	वापस lbs_threshold_पढ़ो(TLV_TYPE_SNR_HIGH, CMD_SUBSCRIBE_SNR_HIGH,
				  file, userbuf, count, ppos);
पूर्ण


अटल sमाप_प्रकार lbs_highsnr_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	वापस lbs_threshold_ग_लिखो(TLV_TYPE_SNR_HIGH, CMD_SUBSCRIBE_SNR_HIGH,
				   file, userbuf, count, ppos);
पूर्ण

अटल sमाप_प्रकार lbs_bcnmiss_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	वापस lbs_threshold_पढ़ो(TLV_TYPE_BCNMISS, CMD_SUBSCRIBE_BCNMISS,
				  file, userbuf, count, ppos);
पूर्ण


अटल sमाप_प्रकार lbs_bcnmiss_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	वापस lbs_threshold_ग_लिखो(TLV_TYPE_BCNMISS, CMD_SUBSCRIBE_BCNMISS,
				   file, userbuf, count, ppos);
पूर्ण


अटल sमाप_प्रकार lbs_rdmac_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा lbs_निजी *priv = file->निजी_data;
	sमाप_प्रकार pos = 0;
	पूर्णांक ret;
	अचिन्हित दीर्घ addr = get_zeroed_page(GFP_KERNEL);
	अक्षर *buf = (अक्षर *)addr;
	u32 val = 0;

	अगर (!buf)
		वापस -ENOMEM;

	ret = lbs_get_reg(priv, CMD_MAC_REG_ACCESS, priv->mac_offset, &val);
	mdelay(10);
	अगर (!ret) अणु
		pos = snम_लिखो(buf, len, "MAC[0x%x] = 0x%08x\n",
				priv->mac_offset, val);
		ret = simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, pos);
	पूर्ण
	मुक्त_page(addr);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार lbs_rdmac_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *userbuf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा lbs_निजी *priv = file->निजी_data;
	अक्षर *buf;

	buf = memdup_user_nul(userbuf, min(count, len - 1));
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	priv->mac_offset = simple_म_से_अदीर्घ(buf, शून्य, 16);
	kमुक्त(buf);
	वापस count;
पूर्ण

अटल sमाप_प्रकार lbs_wrmac_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *userbuf,
				    माप_प्रकार count, loff_t *ppos)
अणु

	काष्ठा lbs_निजी *priv = file->निजी_data;
	sमाप_प्रकार res;
	u32 offset, value;
	अक्षर *buf;

	buf = memdup_user_nul(userbuf, min(count, len - 1));
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	res = माला_पूछो(buf, "%x %x", &offset, &value);
	अगर (res != 2) अणु
		res = -EFAULT;
		जाओ out_unlock;
	पूर्ण

	res = lbs_set_reg(priv, CMD_MAC_REG_ACCESS, offset, value);
	mdelay(10);

	अगर (!res)
		res = count;
out_unlock:
	kमुक्त(buf);
	वापस res;
पूर्ण

अटल sमाप_प्रकार lbs_rdbbp_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा lbs_निजी *priv = file->निजी_data;
	sमाप_प्रकार pos = 0;
	पूर्णांक ret;
	अचिन्हित दीर्घ addr = get_zeroed_page(GFP_KERNEL);
	अक्षर *buf = (अक्षर *)addr;
	u32 val;

	अगर (!buf)
		वापस -ENOMEM;

	ret = lbs_get_reg(priv, CMD_BBP_REG_ACCESS, priv->bbp_offset, &val);
	mdelay(10);
	अगर (!ret) अणु
		pos = snम_लिखो(buf, len, "BBP[0x%x] = 0x%08x\n",
				priv->bbp_offset, val);
		ret = simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, pos);
	पूर्ण
	मुक्त_page(addr);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार lbs_rdbbp_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *userbuf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा lbs_निजी *priv = file->निजी_data;
	अक्षर *buf;

	buf = memdup_user_nul(userbuf, min(count, len - 1));
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	priv->bbp_offset = simple_म_से_अदीर्घ(buf, शून्य, 16);
	kमुक्त(buf);

	वापस count;
पूर्ण

अटल sमाप_प्रकार lbs_wrbbp_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *userbuf,
				    माप_प्रकार count, loff_t *ppos)
अणु

	काष्ठा lbs_निजी *priv = file->निजी_data;
	sमाप_प्रकार res;
	u32 offset, value;
	अक्षर *buf;

	buf = memdup_user_nul(userbuf, min(count, len - 1));
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	res = माला_पूछो(buf, "%x %x", &offset, &value);
	अगर (res != 2) अणु
		res = -EFAULT;
		जाओ out_unlock;
	पूर्ण

	res = lbs_set_reg(priv, CMD_BBP_REG_ACCESS, offset, value);
	mdelay(10);

	अगर (!res)
		res = count;
out_unlock:
	kमुक्त(buf);
	वापस res;
पूर्ण

अटल sमाप_प्रकार lbs_rdrf_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा lbs_निजी *priv = file->निजी_data;
	sमाप_प्रकार pos = 0;
	पूर्णांक ret;
	अचिन्हित दीर्घ addr = get_zeroed_page(GFP_KERNEL);
	अक्षर *buf = (अक्षर *)addr;
	u32 val;

	अगर (!buf)
		वापस -ENOMEM;

	ret = lbs_get_reg(priv, CMD_RF_REG_ACCESS, priv->rf_offset, &val);
	mdelay(10);
	अगर (!ret) अणु
		pos = snम_लिखो(buf, len, "RF[0x%x] = 0x%08x\n",
				priv->rf_offset, val);
		ret = simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, pos);
	पूर्ण
	मुक्त_page(addr);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार lbs_rdrf_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *userbuf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा lbs_निजी *priv = file->निजी_data;
	अक्षर *buf;

	buf = memdup_user_nul(userbuf, min(count, len - 1));
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	priv->rf_offset = simple_म_से_अदीर्घ(buf, शून्य, 16);
	kमुक्त(buf);
	वापस count;
पूर्ण

अटल sमाप_प्रकार lbs_wrrf_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *userbuf,
				    माप_प्रकार count, loff_t *ppos)
अणु

	काष्ठा lbs_निजी *priv = file->निजी_data;
	sमाप_प्रकार res;
	u32 offset, value;
	अक्षर *buf;

	buf = memdup_user_nul(userbuf, min(count, len - 1));
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	res = माला_पूछो(buf, "%x %x", &offset, &value);
	अगर (res != 2) अणु
		res = -EFAULT;
		जाओ out_unlock;
	पूर्ण

	res = lbs_set_reg(priv, CMD_RF_REG_ACCESS, offset, value);
	mdelay(10);

	अगर (!res)
		res = count;
out_unlock:
	kमुक्त(buf);
	वापस res;
पूर्ण

#घोषणा FOPS(ख_पढ़ो, ख_डालो) अणु \
	.owner = THIS_MODULE, \
	.खोलो = simple_खोलो, \
	.पढ़ो = (ख_पढ़ो), \
	.ग_लिखो = (ख_डालो), \
	.llseek = generic_file_llseek, \
पूर्ण

काष्ठा lbs_debugfs_files अणु
	स्थिर अक्षर *name;
	umode_t perm;
	काष्ठा file_operations fops;
पूर्ण;

अटल स्थिर काष्ठा lbs_debugfs_files debugfs_files[] = अणु
	अणु "info", 0444, FOPS(lbs_dev_info, ग_लिखो_file_dummy), पूर्ण,
	अणु "sleepparams", 0644, FOPS(lbs_sleepparams_पढ़ो,
				lbs_sleepparams_ग_लिखो), पूर्ण,
	अणु "hostsleep", 0644, FOPS(lbs_host_sleep_पढ़ो,
				lbs_host_sleep_ग_लिखो), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा lbs_debugfs_files debugfs_events_files[] = अणु
	अणु"low_rssi", 0644, FOPS(lbs_lowrssi_पढ़ो,
				lbs_lowrssi_ग_लिखो), पूर्ण,
	अणु"low_snr", 0644, FOPS(lbs_lowsnr_पढ़ो,
				lbs_lowsnr_ग_लिखो), पूर्ण,
	अणु"failure_count", 0644, FOPS(lbs_failcount_पढ़ो,
				lbs_failcount_ग_लिखो), पूर्ण,
	अणु"beacon_missed", 0644, FOPS(lbs_bcnmiss_पढ़ो,
				lbs_bcnmiss_ग_लिखो), पूर्ण,
	अणु"high_rssi", 0644, FOPS(lbs_highrssi_पढ़ो,
				lbs_highrssi_ग_लिखो), पूर्ण,
	अणु"high_snr", 0644, FOPS(lbs_highsnr_पढ़ो,
				lbs_highsnr_ग_लिखो), पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा lbs_debugfs_files debugfs_regs_files[] = अणु
	अणु"rdmac", 0644, FOPS(lbs_rdmac_पढ़ो, lbs_rdmac_ग_लिखो), पूर्ण,
	अणु"wrmac", 0600, FOPS(शून्य, lbs_wrmac_ग_लिखो), पूर्ण,
	अणु"rdbbp", 0644, FOPS(lbs_rdbbp_पढ़ो, lbs_rdbbp_ग_लिखो), पूर्ण,
	अणु"wrbbp", 0600, FOPS(शून्य, lbs_wrbbp_ग_लिखो), पूर्ण,
	अणु"rdrf", 0644, FOPS(lbs_rdrf_पढ़ो, lbs_rdrf_ग_लिखो), पूर्ण,
	अणु"wrrf", 0600, FOPS(शून्य, lbs_wrrf_ग_लिखो), पूर्ण,
पूर्ण;

व्योम lbs_debugfs_init(व्योम)
अणु
	अगर (!lbs_dir)
		lbs_dir = debugfs_create_dir("lbs_wireless", शून्य);
पूर्ण

व्योम lbs_debugfs_हटाओ(व्योम)
अणु
	debugfs_हटाओ(lbs_dir);
पूर्ण

व्योम lbs_debugfs_init_one(काष्ठा lbs_निजी *priv, काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	स्थिर काष्ठा lbs_debugfs_files *files;
	अगर (!lbs_dir)
		जाओ निकास;

	priv->debugfs_dir = debugfs_create_dir(dev->name, lbs_dir);

	क्रम (i=0; i<ARRAY_SIZE(debugfs_files); i++) अणु
		files = &debugfs_files[i];
		priv->debugfs_files[i] = debugfs_create_file(files->name,
							     files->perm,
							     priv->debugfs_dir,
							     priv,
							     &files->fops);
	पूर्ण

	priv->events_dir = debugfs_create_dir("subscribed_events", priv->debugfs_dir);

	क्रम (i=0; i<ARRAY_SIZE(debugfs_events_files); i++) अणु
		files = &debugfs_events_files[i];
		priv->debugfs_events_files[i] = debugfs_create_file(files->name,
							     files->perm,
							     priv->events_dir,
							     priv,
							     &files->fops);
	पूर्ण

	priv->regs_dir = debugfs_create_dir("registers", priv->debugfs_dir);

	क्रम (i=0; i<ARRAY_SIZE(debugfs_regs_files); i++) अणु
		files = &debugfs_regs_files[i];
		priv->debugfs_regs_files[i] = debugfs_create_file(files->name,
							     files->perm,
							     priv->regs_dir,
							     priv,
							     &files->fops);
	पूर्ण

#अगर_घोषित PROC_DEBUG
	lbs_debug_init(priv);
#पूर्ण_अगर
निकास:
	वापस;
पूर्ण

व्योम lbs_debugfs_हटाओ_one(काष्ठा lbs_निजी *priv)
अणु
	पूर्णांक i;

	क्रम(i=0; i<ARRAY_SIZE(debugfs_regs_files); i++)
		debugfs_हटाओ(priv->debugfs_regs_files[i]);

	debugfs_हटाओ(priv->regs_dir);

	क्रम(i=0; i<ARRAY_SIZE(debugfs_events_files); i++)
		debugfs_हटाओ(priv->debugfs_events_files[i]);

	debugfs_हटाओ(priv->events_dir);
#अगर_घोषित PROC_DEBUG
	debugfs_हटाओ(priv->debugfs_debug);
#पूर्ण_अगर
	क्रम(i=0; i<ARRAY_SIZE(debugfs_files); i++)
		debugfs_हटाओ(priv->debugfs_files[i]);
	debugfs_हटाओ(priv->debugfs_dir);
पूर्ण



/* debug entry */

#अगर_घोषित PROC_DEBUG

#घोषणा item_size(n)	(माप_field(काष्ठा lbs_निजी, n))
#घोषणा item_addr(n)	(दुरत्व(काष्ठा lbs_निजी, n))


काष्ठा debug_data अणु
	अक्षर name[32];
	u32 size;
	माप_प्रकार addr;
पूर्ण;

/* To debug any member of काष्ठा lbs_निजी, simply add one line here.
 */
अटल काष्ठा debug_data items[] = अणु
	अणु"psmode", item_size(psmode), item_addr(psmode)पूर्ण,
	अणु"psstate", item_size(psstate), item_addr(psstate)पूर्ण,
पूर्ण;

अटल पूर्णांक num_of_items = ARRAY_SIZE(items);

/**
 * lbs_debugfs_पढ़ो - proc पढ़ो function
 *
 * @file:	file to पढ़ो
 * @userbuf:	poपूर्णांकer to buffer
 * @count:	number of bytes to पढ़ो
 * @ppos:	पढ़ो data starting position
 *
 * वापसs:	amount of data पढ़ो or negative error code
 */
अटल sमाप_प्रकार lbs_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
			माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक val = 0;
	माप_प्रकार pos = 0;
	sमाप_प्रकार res;
	अक्षर *p;
	पूर्णांक i;
	काष्ठा debug_data *d;
	अचिन्हित दीर्घ addr = get_zeroed_page(GFP_KERNEL);
	अक्षर *buf = (अक्षर *)addr;
	अगर (!buf)
		वापस -ENOMEM;

	p = buf;

	d = file->निजी_data;

	क्रम (i = 0; i < num_of_items; i++) अणु
		अगर (d[i].size == 1)
			val = *((u8 *) d[i].addr);
		अन्यथा अगर (d[i].size == 2)
			val = *((u16 *) d[i].addr);
		अन्यथा अगर (d[i].size == 4)
			val = *((u32 *) d[i].addr);
		अन्यथा अगर (d[i].size == 8)
			val = *((u64 *) d[i].addr);

		pos += प्र_लिखो(p + pos, "%s=%d\n", d[i].name, val);
	पूर्ण

	res = simple_पढ़ो_from_buffer(userbuf, count, ppos, p, pos);

	मुक्त_page(addr);
	वापस res;
पूर्ण

/**
 * lbs_debugfs_ग_लिखो - proc ग_लिखो function
 *
 * @f:		file poपूर्णांकer
 * @buf:	poपूर्णांकer to data buffer
 * @cnt:	data number to ग_लिखो
 * @ppos:	file position
 *
 * वापसs:	amount of data written
 */
अटल sमाप_प्रकार lbs_debugfs_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
			    माप_प्रकार cnt, loff_t *ppos)
अणु
	पूर्णांक r, i;
	अक्षर *pdata;
	अक्षर *p;
	अक्षर *p0;
	अक्षर *p1;
	अक्षर *p2;
	काष्ठा debug_data *d = f->निजी_data;

	अगर (cnt == 0)
		वापस 0;

	pdata = memdup_user_nul(buf, cnt);
	अगर (IS_ERR(pdata))
		वापस PTR_ERR(pdata);

	p0 = pdata;
	क्रम (i = 0; i < num_of_items; i++) अणु
		करो अणु
			p = म_माला(p0, d[i].name);
			अगर (p == शून्य)
				अवरोध;
			p1 = म_अक्षर(p, '\n');
			अगर (p1 == शून्य)
				अवरोध;
			p0 = p1++;
			p2 = म_अक्षर(p, '=');
			अगर (!p2)
				अवरोध;
			p2++;
			r = simple_म_से_अदीर्घ(p2, शून्य, 0);
			अगर (d[i].size == 1)
				*((u8 *) d[i].addr) = (u8) r;
			अन्यथा अगर (d[i].size == 2)
				*((u16 *) d[i].addr) = (u16) r;
			अन्यथा अगर (d[i].size == 4)
				*((u32 *) d[i].addr) = (u32) r;
			अन्यथा अगर (d[i].size == 8)
				*((u64 *) d[i].addr) = (u64) r;
			अवरोध;
		पूर्ण जबतक (1);
	पूर्ण
	kमुक्त(pdata);

	वापस (sमाप_प्रकार)cnt;
पूर्ण

अटल स्थिर काष्ठा file_operations lbs_debug_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.ग_लिखो = lbs_debugfs_ग_लिखो,
	.पढ़ो = lbs_debugfs_पढ़ो,
	.llseek = शेष_llseek,
पूर्ण;

/**
 * lbs_debug_init - create debug proc file
 *
 * @priv:	poपूर्णांकer to &काष्ठा lbs_निजी
 *
 * वापसs:	N/A
 */
अटल व्योम lbs_debug_init(काष्ठा lbs_निजी *priv)
अणु
	पूर्णांक i;

	अगर (!priv->debugfs_dir)
		वापस;

	क्रम (i = 0; i < num_of_items; i++)
		items[i].addr += (माप_प्रकार) priv;

	priv->debugfs_debug = debugfs_create_file("debug", 0644,
						  priv->debugfs_dir, &items[0],
						  &lbs_debug_fops);
पूर्ण
#पूर्ण_अगर
