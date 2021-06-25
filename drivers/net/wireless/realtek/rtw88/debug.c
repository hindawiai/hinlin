<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश "main.h"
#समावेश "coex.h"
#समावेश "sec.h"
#समावेश "fw.h"
#समावेश "debug.h"
#समावेश "phy.h"
#समावेश "reg.h"

#अगर_घोषित CONFIG_RTW88_DEBUGFS

काष्ठा rtw_debugfs_priv अणु
	काष्ठा rtw_dev *rtwdev;
	पूर्णांक (*cb_पढ़ो)(काष्ठा seq_file *m, व्योम *v);
	sमाप_प्रकार (*cb_ग_लिखो)(काष्ठा file *filp, स्थिर अक्षर __user *buffer,
			    माप_प्रकार count, loff_t *loff);
	जोड़ अणु
		u32 cb_data;
		u8 *buf;
		काष्ठा अणु
			u32 page_offset;
			u32 page_num;
		पूर्ण rsvd_page;
		काष्ठा अणु
			u8 rf_path;
			u32 rf_addr;
			u32 rf_mask;
		पूर्ण;
		काष्ठा अणु
			u32 addr;
			u32 len;
		पूर्ण पढ़ो_reg;
		काष्ठा अणु
			u8 bit;
		पूर्ण dm_cap;
	पूर्ण;
पूर्ण;

अटल स्थिर अक्षर * स्थिर rtw_dm_cap_strs[] = अणु
	[RTW_DM_CAP_NA] = "NA",
	[RTW_DM_CAP_TXGAPK] = "TXGAPK",
पूर्ण;

अटल पूर्णांक rtw_debugfs_single_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = m->निजी;

	वापस debugfs_priv->cb_पढ़ो(m, v);
पूर्ण

अटल sमाप_प्रकार rtw_debugfs_common_ग_लिखो(काष्ठा file *filp,
					स्थिर अक्षर __user *buffer,
					माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = filp->निजी_data;

	वापस debugfs_priv->cb_ग_लिखो(filp, buffer, count, loff);
पूर्ण

अटल sमाप_प्रकार rtw_debugfs_single_ग_लिखो(काष्ठा file *filp,
					स्थिर अक्षर __user *buffer,
					माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा seq_file *seqpriv = (काष्ठा seq_file *)filp->निजी_data;
	काष्ठा rtw_debugfs_priv *debugfs_priv = seqpriv->निजी;

	वापस debugfs_priv->cb_ग_लिखो(filp, buffer, count, loff);
पूर्ण

अटल पूर्णांक rtw_debugfs_single_खोलो_rw(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, rtw_debugfs_single_show, inode->i_निजी);
पूर्ण

अटल पूर्णांक rtw_debugfs_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations file_ops_single_r = अणु
	.owner = THIS_MODULE,
	.खोलो = rtw_debugfs_single_खोलो_rw,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations file_ops_single_rw = अणु
	.owner = THIS_MODULE,
	.खोलो = rtw_debugfs_single_खोलो_rw,
	.release = single_release,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.ग_लिखो = rtw_debugfs_single_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा file_operations file_ops_common_ग_लिखो = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = rtw_debugfs_common_ग_लिखो,
	.खोलो = simple_खोलो,
	.release = rtw_debugfs_बंद,
पूर्ण;

अटल पूर्णांक rtw_debugfs_get_पढ़ो_reg(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	u32 val, len, addr;

	len = debugfs_priv->पढ़ो_reg.len;
	addr = debugfs_priv->पढ़ो_reg.addr;
	चयन (len) अणु
	हाल 1:
		val = rtw_पढ़ो8(rtwdev, addr);
		seq_म_लिखो(m, "reg 0x%03x: 0x%02x\n", addr, val);
		अवरोध;
	हाल 2:
		val = rtw_पढ़ो16(rtwdev, addr);
		seq_म_लिखो(m, "reg 0x%03x: 0x%04x\n", addr, val);
		अवरोध;
	हाल 4:
		val = rtw_पढ़ो32(rtwdev, addr);
		seq_म_लिखो(m, "reg 0x%03x: 0x%08x\n", addr, val);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_debugfs_get_rf_पढ़ो(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	u32 val, addr, mask;
	u8 path;

	path = debugfs_priv->rf_path;
	addr = debugfs_priv->rf_addr;
	mask = debugfs_priv->rf_mask;

	val = rtw_पढ़ो_rf(rtwdev, path, addr, mask);

	seq_म_लिखो(m, "rf_read path:%d addr:0x%08x mask:0x%08x val=0x%08x\n",
		   path, addr, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_debugfs_copy_from_user(अक्षर पंचांगp[], पूर्णांक size,
				      स्थिर अक्षर __user *buffer, माप_प्रकार count,
				      पूर्णांक num)
अणु
	पूर्णांक पंचांगp_len;

	स_रखो(पंचांगp, 0, size);

	अगर (count < num)
		वापस -EFAULT;

	पंचांगp_len = (count > size - 1 ? size - 1 : count);

	अगर (!buffer || copy_from_user(पंचांगp, buffer, पंचांगp_len))
		वापस count;

	पंचांगp[पंचांगp_len] = '\0';

	वापस 0;
पूर्ण

अटल sमाप_प्रकार rtw_debugfs_set_पढ़ो_reg(काष्ठा file *filp,
					स्थिर अक्षर __user *buffer,
					माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा seq_file *seqpriv = (काष्ठा seq_file *)filp->निजी_data;
	काष्ठा rtw_debugfs_priv *debugfs_priv = seqpriv->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	अक्षर पंचांगp[32 + 1];
	u32 addr, len;
	पूर्णांक num;

	rtw_debugfs_copy_from_user(पंचांगp, माप(पंचांगp), buffer, count, 2);

	num = माला_पूछो(पंचांगp, "%x %x", &addr, &len);

	अगर (num !=  2)
		वापस count;

	अगर (len != 1 && len != 2 && len != 4) अणु
		rtw_warn(rtwdev, "read reg setting wrong len\n");
		वापस -EINVAL;
	पूर्ण
	debugfs_priv->पढ़ो_reg.addr = addr;
	debugfs_priv->पढ़ो_reg.len = len;

	वापस count;
पूर्ण

अटल पूर्णांक rtw_debugfs_get_dump_cam(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	u32 val, command;
	u32 hw_key_idx = debugfs_priv->cb_data << RTW_SEC_CAM_ENTRY_SHIFT;
	u32 पढ़ो_cmd = RTW_SEC_CMD_POLLING;
	पूर्णांक i;

	seq_म_लिखो(m, "cam entry%d\n", debugfs_priv->cb_data);
	seq_माला_दो(m, "0x0      0x1      0x2     0x3     ");
	seq_माला_दो(m, "0x4     0x5\n");
	mutex_lock(&rtwdev->mutex);
	क्रम (i = 0; i <= 5; i++) अणु
		command = पढ़ो_cmd | (hw_key_idx + i);
		rtw_ग_लिखो32(rtwdev, RTW_SEC_CMD_REG, command);
		val = rtw_पढ़ो32(rtwdev, RTW_SEC_READ_REG);
		seq_म_लिखो(m, "%8.8x", val);
		अगर (i < 2)
			seq_माला_दो(m, " ");
	पूर्ण
	seq_माला_दो(m, "\n");
	mutex_unlock(&rtwdev->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_debugfs_get_rsvd_page(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	u8 page_size = rtwdev->chip->page_size;
	u32 buf_size = debugfs_priv->rsvd_page.page_num * page_size;
	u32 offset = debugfs_priv->rsvd_page.page_offset * page_size;
	u8 *buf;
	पूर्णांक i;
	पूर्णांक ret;

	buf = vzalloc(buf_size);
	अगर (!buf)
		वापस -ENOMEM;

	ret = rtw_fw_dump_fअगरo(rtwdev, RTW_FW_FIFO_SEL_RSVD_PAGE, offset,
			       buf_size, (u32 *)buf);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to dump rsvd page\n");
		vमुक्त(buf);
		वापस ret;
	पूर्ण

	क्रम (i = 0 ; i < buf_size ; i += 8) अणु
		अगर (i % page_size == 0)
			seq_म_लिखो(m, "PAGE %d\n", (i + offset) / page_size);
		seq_म_लिखो(m, "%2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x\n",
			   *(buf + i), *(buf + i + 1),
			   *(buf + i + 2), *(buf + i + 3),
			   *(buf + i + 4), *(buf + i + 5),
			   *(buf + i + 6), *(buf + i + 7));
	पूर्ण
	vमुक्त(buf);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार rtw_debugfs_set_rsvd_page(काष्ठा file *filp,
					 स्थिर अक्षर __user *buffer,
					 माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा seq_file *seqpriv = (काष्ठा seq_file *)filp->निजी_data;
	काष्ठा rtw_debugfs_priv *debugfs_priv = seqpriv->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	अक्षर पंचांगp[32 + 1];
	u32 offset, page_num;
	पूर्णांक num;

	rtw_debugfs_copy_from_user(पंचांगp, माप(पंचांगp), buffer, count, 2);

	num = माला_पूछो(पंचांगp, "%d %d", &offset, &page_num);

	अगर (num != 2) अणु
		rtw_warn(rtwdev, "invalid arguments\n");
		वापस -EINVAL;
	पूर्ण

	debugfs_priv->rsvd_page.page_offset = offset;
	debugfs_priv->rsvd_page.page_num = page_num;

	वापस count;
पूर्ण

अटल sमाप_प्रकार rtw_debugfs_set_single_input(काष्ठा file *filp,
					    स्थिर अक्षर __user *buffer,
					    माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा seq_file *seqpriv = (काष्ठा seq_file *)filp->निजी_data;
	काष्ठा rtw_debugfs_priv *debugfs_priv = seqpriv->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	अक्षर पंचांगp[32 + 1];
	u32 input;
	पूर्णांक num;

	rtw_debugfs_copy_from_user(पंचांगp, माप(पंचांगp), buffer, count, 1);

	num = kstrtoपूर्णांक(पंचांगp, 0, &input);

	अगर (num) अणु
		rtw_warn(rtwdev, "kstrtoint failed\n");
		वापस num;
	पूर्ण

	debugfs_priv->cb_data = input;

	वापस count;
पूर्ण

अटल sमाप_प्रकार rtw_debugfs_set_ग_लिखो_reg(काष्ठा file *filp,
					 स्थिर अक्षर __user *buffer,
					 माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = filp->निजी_data;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	अक्षर पंचांगp[32 + 1];
	u32 addr, val, len;
	पूर्णांक num;

	rtw_debugfs_copy_from_user(पंचांगp, माप(पंचांगp), buffer, count, 3);

	/* ग_लिखो BB/MAC रेजिस्टर */
	num = माला_पूछो(पंचांगp, "%x %x %x", &addr, &val, &len);

	अगर (num !=  3)
		वापस count;

	चयन (len) अणु
	हाल 1:
		rtw_dbg(rtwdev, RTW_DBG_DEBUGFS,
			"reg write8 0x%03x: 0x%08x\n", addr, val);
		rtw_ग_लिखो8(rtwdev, addr, (u8)val);
		अवरोध;
	हाल 2:
		rtw_dbg(rtwdev, RTW_DBG_DEBUGFS,
			"reg write16 0x%03x: 0x%08x\n", addr, val);
		rtw_ग_लिखो16(rtwdev, addr, (u16)val);
		अवरोध;
	हाल 4:
		rtw_dbg(rtwdev, RTW_DBG_DEBUGFS,
			"reg write32 0x%03x: 0x%08x\n", addr, val);
		rtw_ग_लिखो32(rtwdev, addr, (u32)val);
		अवरोध;
	शेष:
		rtw_dbg(rtwdev, RTW_DBG_DEBUGFS,
			"error write length = %d\n", len);
		अवरोध;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार rtw_debugfs_set_h2c(काष्ठा file *filp,
				   स्थिर अक्षर __user *buffer,
				   माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = filp->निजी_data;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	अक्षर पंचांगp[32 + 1];
	u8 param[8];
	पूर्णांक num;

	rtw_debugfs_copy_from_user(पंचांगp, माप(पंचांगp), buffer, count, 3);

	num = माला_पूछो(पंचांगp, "%hhx,%hhx,%hhx,%hhx,%hhx,%hhx,%hhx,%hhx",
		     &param[0], &param[1], &param[2], &param[3],
		     &param[4], &param[5], &param[6], &param[7]);
	अगर (num != 8) अणु
		rtw_info(rtwdev, "invalid H2C command format for debug\n");
		वापस -EINVAL;
	पूर्ण

	rtw_fw_h2c_cmd_dbg(rtwdev, param);

	वापस count;
पूर्ण

अटल sमाप_प्रकार rtw_debugfs_set_rf_ग_लिखो(काष्ठा file *filp,
					स्थिर अक्षर __user *buffer,
					माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = filp->निजी_data;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	अक्षर पंचांगp[32 + 1];
	u32 path, addr, mask, val;
	पूर्णांक num;

	rtw_debugfs_copy_from_user(पंचांगp, माप(पंचांगp), buffer, count, 4);

	num = माला_पूछो(पंचांगp, "%x %x %x %x", &path, &addr, &mask, &val);

	अगर (num !=  4) अणु
		rtw_warn(rtwdev, "invalid args, [path] [addr] [mask] [val]\n");
		वापस count;
	पूर्ण

	rtw_ग_लिखो_rf(rtwdev, path, addr, mask, val);
	rtw_dbg(rtwdev, RTW_DBG_DEBUGFS,
		"write_rf path:%d addr:0x%08x mask:0x%08x, val:0x%08x\n",
		path, addr, mask, val);

	वापस count;
पूर्ण

अटल sमाप_प्रकार rtw_debugfs_set_rf_पढ़ो(काष्ठा file *filp,
				       स्थिर अक्षर __user *buffer,
				       माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा seq_file *seqpriv = (काष्ठा seq_file *)filp->निजी_data;
	काष्ठा rtw_debugfs_priv *debugfs_priv = seqpriv->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	अक्षर पंचांगp[32 + 1];
	u32 path, addr, mask;
	पूर्णांक num;

	rtw_debugfs_copy_from_user(पंचांगp, माप(पंचांगp), buffer, count, 3);

	num = माला_पूछो(पंचांगp, "%x %x %x", &path, &addr, &mask);

	अगर (num !=  3) अणु
		rtw_warn(rtwdev, "invalid args, [path] [addr] [mask] [val]\n");
		वापस count;
	पूर्ण

	debugfs_priv->rf_path = path;
	debugfs_priv->rf_addr = addr;
	debugfs_priv->rf_mask = mask;

	वापस count;
पूर्ण

अटल पूर्णांक rtw_debug_get_mac_page(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	u32 page = debugfs_priv->cb_data;
	पूर्णांक i, n;
	पूर्णांक max = 0xff;

	rtw_पढ़ो32(rtwdev, debugfs_priv->cb_data);
	क्रम (n = 0; n <= max; ) अणु
		seq_म_लिखो(m, "\n%8.8x  ", n + page);
		क्रम (i = 0; i < 4 && n <= max; i++, n += 4)
			seq_म_लिखो(m, "%8.8x    ",
				   rtw_पढ़ो32(rtwdev, (page | n)));
	पूर्ण
	seq_माला_दो(m, "\n");
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_debug_get_bb_page(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	u32 page = debugfs_priv->cb_data;
	पूर्णांक i, n;
	पूर्णांक max = 0xff;

	rtw_पढ़ो32(rtwdev, debugfs_priv->cb_data);
	क्रम (n = 0; n <= max; ) अणु
		seq_म_लिखो(m, "\n%8.8x  ", n + page);
		क्रम (i = 0; i < 4 && n <= max; i++, n += 4)
			seq_म_लिखो(m, "%8.8x    ",
				   rtw_पढ़ो32(rtwdev, (page | n)));
	पूर्ण
	seq_माला_दो(m, "\n");
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_debug_get_rf_dump(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	u32 addr, offset, data;
	u8 path;

	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
		seq_म_लिखो(m, "RF path:%d\n", path);
		क्रम (addr = 0; addr < 0x100; addr += 4) अणु
			seq_म_लिखो(m, "%8.8x  ", addr);
			क्रम (offset = 0; offset < 4; offset++) अणु
				data = rtw_पढ़ो_rf(rtwdev, path, addr + offset,
						   0xffffffff);
				seq_म_लिखो(m, "%8.8x    ", data);
			पूर्ण
			seq_माला_दो(m, "\n");
		पूर्ण
		seq_माला_दो(m, "\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rtw_prपूर्णांक_cck_rate_txt(काष्ठा seq_file *m, u8 rate)
अणु
	अटल स्थिर अक्षर * स्थिर
	cck_rate[] = अणु"1M", "2M", "5.5M", "11M"पूर्ण;
	u8 idx = rate - DESC_RATE1M;

	seq_म_लिखो(m, " CCK_%-5s", cck_rate[idx]);
पूर्ण

अटल व्योम rtw_prपूर्णांक_ofdm_rate_txt(काष्ठा seq_file *m, u8 rate)
अणु
	अटल स्थिर अक्षर * स्थिर
	ofdm_rate[] = अणु"6M", "9M", "12M", "18M", "24M", "36M", "48M", "54M"पूर्ण;
	u8 idx = rate - DESC_RATE6M;

	seq_म_लिखो(m, " OFDM_%-4s", ofdm_rate[idx]);
पूर्ण

अटल व्योम rtw_prपूर्णांक_ht_rate_txt(काष्ठा seq_file *m, u8 rate)
अणु
	u8 mcs_n = rate - DESC_RATEMCS0;

	seq_म_लिखो(m, " MCS%-6u", mcs_n);
पूर्ण

अटल व्योम rtw_prपूर्णांक_vht_rate_txt(काष्ठा seq_file *m, u8 rate)
अणु
	u8 idx = rate - DESC_RATEVHT1SS_MCS0;
	u8 n_ss, mcs_n;

	/* n spatial stream */
	n_ss = 1 + idx / 10;
	/* MCS n */
	mcs_n = idx % 10;
	seq_म_लिखो(m, " VHT%uSMCS%u", n_ss, mcs_n);
पूर्ण

अटल व्योम rtw_prपूर्णांक_rate(काष्ठा seq_file *m, u8 rate)
अणु
	चयन (rate) अणु
	हाल DESC_RATE1M...DESC_RATE11M:
		rtw_prपूर्णांक_cck_rate_txt(m, rate);
		अवरोध;
	हाल DESC_RATE6M...DESC_RATE54M:
		rtw_prपूर्णांक_ofdm_rate_txt(m, rate);
		अवरोध;
	हाल DESC_RATEMCS0...DESC_RATEMCS15:
		rtw_prपूर्णांक_ht_rate_txt(m, rate);
		अवरोध;
	हाल DESC_RATEVHT1SS_MCS0...DESC_RATEVHT2SS_MCS9:
		rtw_prपूर्णांक_vht_rate_txt(m, rate);
		अवरोध;
	शेष:
		seq_म_लिखो(m, " Unknown rate=0x%x\n", rate);
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा हाल_REGD(src) \
	हाल RTW_REGD_##src: वापस #src

अटल स्थिर अक्षर *rtw_get_regd_string(u8 regd)
अणु
	चयन (regd) अणु
	हाल_REGD(FCC);
	हाल_REGD(MKK);
	हाल_REGD(ETSI);
	हाल_REGD(IC);
	हाल_REGD(KCC);
	हाल_REGD(ACMA);
	हाल_REGD(CHILE);
	हाल_REGD(UKRAINE);
	हाल_REGD(MEXICO);
	हाल_REGD(CN);
	हाल_REGD(WW);
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल पूर्णांक rtw_debugfs_get_tx_pwr_tbl(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u8 path, rate;
	काष्ठा rtw_घातer_params pwr_param = अणु0पूर्ण;
	u8 bw = hal->current_band_width;
	u8 ch = hal->current_channel;
	u8 regd = rtwdev->regd.txpwr_regd;

	seq_म_लिखो(m, "regulatory: %s\n", rtw_get_regd_string(regd));
	seq_म_लिखो(m, "%-4s %-10s %-3s%6s %-4s %4s (%-4s %-4s) %-4s\n",
		   "path", "rate", "pwr", "", "base", "", "byr", "lmt", "rem");

	mutex_lock(&hal->tx_घातer_mutex);
	क्रम (path = RF_PATH_A; path <= RF_PATH_B; path++) अणु
		/* there is no CCK rates used in 5G */
		अगर (hal->current_band_type == RTW_BAND_5G)
			rate = DESC_RATE6M;
		अन्यथा
			rate = DESC_RATE1M;

		/* now, not support vht 3ss and vht 4ss*/
		क्रम (; rate <= DESC_RATEVHT2SS_MCS9; rate++) अणु
			/* now, not support ht 3ss and ht 4ss*/
			अगर (rate > DESC_RATEMCS15 &&
			    rate < DESC_RATEVHT1SS_MCS0)
				जारी;

			rtw_get_tx_घातer_params(rtwdev, path, rate, bw,
						ch, regd, &pwr_param);

			seq_म_लिखो(m, "%4c ", path + 'A');
			rtw_prपूर्णांक_rate(m, rate);
			seq_म_लिखो(m, " %3u(0x%02x) %4u %4d (%4d %4d) %4d\n",
				   hal->tx_pwr_tbl[path][rate],
				   hal->tx_pwr_tbl[path][rate],
				   pwr_param.pwr_base,
				   min_t(s8, pwr_param.pwr_offset,
					 pwr_param.pwr_limit),
				   pwr_param.pwr_offset, pwr_param.pwr_limit,
				   pwr_param.pwr_remnant);
		पूर्ण
	पूर्ण

	mutex_unlock(&hal->tx_घातer_mutex);

	वापस 0;
पूर्ण

व्योम rtw_debugfs_get_simple_phy_info(काष्ठा seq_file *m)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_traffic_stats *stats = &rtwdev->stats;

	seq_म_लिखो(m, "%-40s = %ddBm/ %d\n", "RSSI/ STA Channel",
		   dm_info->rssi[RF_PATH_A] - 100, hal->current_channel);

	seq_म_लिखो(m, "TP {Tx, Rx} = {%u, %u}Mbps\n",
		   stats->tx_throughput, stats->rx_throughput);

	seq_माला_दो(m, "[Tx Rate] = ");
	rtw_prपूर्णांक_rate(m, dm_info->tx_rate);
	seq_म_लिखो(m, "(0x%x)\n", dm_info->tx_rate);

	seq_माला_दो(m, "[Rx Rate] = ");
	rtw_prपूर्णांक_rate(m, dm_info->curr_rx_rate);
	seq_म_लिखो(m, "(0x%x)\n", dm_info->curr_rx_rate);
पूर्ण

अटल पूर्णांक rtw_debugfs_get_phy_info(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_traffic_stats *stats = &rtwdev->stats;
	काष्ठा rtw_pkt_count *last_cnt = &dm_info->last_pkt_count;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा ewma_evm *ewma_evm = dm_info->ewma_evm;
	काष्ठा ewma_snr *ewma_snr = dm_info->ewma_snr;
	u8 ss, rate_id;

	seq_माला_दो(m, "==========[Common Info]========\n");
	seq_म_लिखो(m, "Is link = %c\n", rtw_is_assoc(rtwdev) ? 'Y' : 'N');
	seq_म_लिखो(m, "Current CH(fc) = %u\n", rtwdev->hal.current_channel);
	seq_म_लिखो(m, "Current BW = %u\n", rtwdev->hal.current_band_width);
	seq_म_लिखो(m, "Current IGI = 0x%x\n", dm_info->igi_history[0]);
	seq_म_लिखो(m, "TP {Tx, Rx} = {%u, %u}Mbps\n\n",
		   stats->tx_throughput, stats->rx_throughput);

	seq_माला_दो(m, "==========[Tx Phy Info]========\n");
	seq_माला_दो(m, "[Tx Rate] = ");
	rtw_prपूर्णांक_rate(m, dm_info->tx_rate);
	seq_म_लिखो(m, "(0x%x)\n\n", dm_info->tx_rate);

	seq_माला_दो(m, "==========[Rx Phy Info]========\n");
	seq_म_लिखो(m, "[Rx Beacon Count] = %u\n", last_cnt->num_bcn_pkt);
	seq_माला_दो(m, "[Rx Rate] = ");
	rtw_prपूर्णांक_rate(m, dm_info->curr_rx_rate);
	seq_म_लिखो(m, "(0x%x)\n", dm_info->curr_rx_rate);

	seq_माला_दो(m, "[Rx Rate Count]:\n");
	seq_म_लिखो(m, " * CCK = {%u, %u, %u, %u}\n",
		   last_cnt->num_qry_pkt[DESC_RATE1M],
		   last_cnt->num_qry_pkt[DESC_RATE2M],
		   last_cnt->num_qry_pkt[DESC_RATE5_5M],
		   last_cnt->num_qry_pkt[DESC_RATE11M]);

	seq_म_लिखो(m, " * OFDM = {%u, %u, %u, %u, %u, %u, %u, %u}\n",
		   last_cnt->num_qry_pkt[DESC_RATE6M],
		   last_cnt->num_qry_pkt[DESC_RATE9M],
		   last_cnt->num_qry_pkt[DESC_RATE12M],
		   last_cnt->num_qry_pkt[DESC_RATE18M],
		   last_cnt->num_qry_pkt[DESC_RATE24M],
		   last_cnt->num_qry_pkt[DESC_RATE36M],
		   last_cnt->num_qry_pkt[DESC_RATE48M],
		   last_cnt->num_qry_pkt[DESC_RATE54M]);

	क्रम (ss = 0; ss < efuse->hw_cap.nss; ss++) अणु
		rate_id = DESC_RATEMCS0 + ss * 8;
		seq_म_लिखो(m, " * HT_MCS[%u:%u] = {%u, %u, %u, %u, %u, %u, %u, %u}\n",
			   ss * 8, ss * 8 + 7,
			   last_cnt->num_qry_pkt[rate_id],
			   last_cnt->num_qry_pkt[rate_id + 1],
			   last_cnt->num_qry_pkt[rate_id + 2],
			   last_cnt->num_qry_pkt[rate_id + 3],
			   last_cnt->num_qry_pkt[rate_id + 4],
			   last_cnt->num_qry_pkt[rate_id + 5],
			   last_cnt->num_qry_pkt[rate_id + 6],
			   last_cnt->num_qry_pkt[rate_id + 7]);
	पूर्ण

	क्रम (ss = 0; ss < efuse->hw_cap.nss; ss++) अणु
		rate_id = DESC_RATEVHT1SS_MCS0 + ss * 10;
		seq_म_लिखो(m, " * VHT_MCS-%uss MCS[0:9] = {%u, %u, %u, %u, %u, %u, %u, %u, %u, %u}\n",
			   ss + 1,
			   last_cnt->num_qry_pkt[rate_id],
			   last_cnt->num_qry_pkt[rate_id + 1],
			   last_cnt->num_qry_pkt[rate_id + 2],
			   last_cnt->num_qry_pkt[rate_id + 3],
			   last_cnt->num_qry_pkt[rate_id + 4],
			   last_cnt->num_qry_pkt[rate_id + 5],
			   last_cnt->num_qry_pkt[rate_id + 6],
			   last_cnt->num_qry_pkt[rate_id + 7],
			   last_cnt->num_qry_pkt[rate_id + 8],
			   last_cnt->num_qry_pkt[rate_id + 9]);
	पूर्ण

	seq_म_लिखो(m, "[RSSI(dBm)] = {%d, %d}\n",
		   dm_info->rssi[RF_PATH_A] - 100,
		   dm_info->rssi[RF_PATH_B] - 100);
	seq_म_लिखो(m, "[Rx EVM(dB)] = {-%d, -%d}\n",
		   dm_info->rx_evm_dbm[RF_PATH_A],
		   dm_info->rx_evm_dbm[RF_PATH_B]);
	seq_म_लिखो(m, "[Rx SNR] = {%d, %d}\n",
		   dm_info->rx_snr[RF_PATH_A],
		   dm_info->rx_snr[RF_PATH_B]);
	seq_म_लिखो(m, "[CFO_tail(KHz)] = {%d, %d}\n",
		   dm_info->cfo_tail[RF_PATH_A],
		   dm_info->cfo_tail[RF_PATH_B]);

	अगर (dm_info->curr_rx_rate >= DESC_RATE11M) अणु
		seq_माला_दो(m, "[Rx Average Status]:\n");
		seq_म_लिखो(m, " * OFDM, EVM: {-%d}, SNR: {%d}\n",
			   (u8)ewma_evm_पढ़ो(&ewma_evm[RTW_EVM_OFDM]),
			   (u8)ewma_snr_पढ़ो(&ewma_snr[RTW_SNR_OFDM_A]));
		seq_म_लिखो(m, " * 1SS, EVM: {-%d}, SNR: {%d}\n",
			   (u8)ewma_evm_पढ़ो(&ewma_evm[RTW_EVM_1SS]),
			   (u8)ewma_snr_पढ़ो(&ewma_snr[RTW_SNR_1SS_A]));
		seq_म_लिखो(m, " * 2SS, EVM: {-%d, -%d}, SNR: {%d, %d}\n",
			   (u8)ewma_evm_पढ़ो(&ewma_evm[RTW_EVM_2SS_A]),
			   (u8)ewma_evm_पढ़ो(&ewma_evm[RTW_EVM_2SS_B]),
			   (u8)ewma_snr_पढ़ो(&ewma_snr[RTW_SNR_2SS_A]),
			   (u8)ewma_snr_पढ़ो(&ewma_snr[RTW_SNR_2SS_B]));
	पूर्ण

	seq_माला_दो(m, "[Rx Counter]:\n");
	seq_म_लिखो(m, " * CCA (CCK, OFDM, Total) = (%u, %u, %u)\n",
		   dm_info->cck_cca_cnt,
		   dm_info->ofdm_cca_cnt,
		   dm_info->total_cca_cnt);
	seq_म_लिखो(m, " * False Alarm (CCK, OFDM, Total) = (%u, %u, %u)\n",
		   dm_info->cck_fa_cnt,
		   dm_info->ofdm_fa_cnt,
		   dm_info->total_fa_cnt);
	seq_म_लिखो(m, " * CCK cnt (ok, err) = (%u, %u)\n",
		   dm_info->cck_ok_cnt, dm_info->cck_err_cnt);
	seq_म_लिखो(m, " * OFDM cnt (ok, err) = (%u, %u)\n",
		   dm_info->ofdm_ok_cnt, dm_info->ofdm_err_cnt);
	seq_म_लिखो(m, " * HT cnt (ok, err) = (%u, %u)\n",
		   dm_info->ht_ok_cnt, dm_info->ht_err_cnt);
	seq_म_लिखो(m, " * VHT cnt (ok, err) = (%u, %u)\n",
		   dm_info->vht_ok_cnt, dm_info->vht_err_cnt);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_debugfs_get_coex_info(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;

	rtw_coex_display_coex_info(rtwdev, m);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार rtw_debugfs_set_coex_enable(काष्ठा file *filp,
					   स्थिर अक्षर __user *buffer,
					   माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा seq_file *seqpriv = (काष्ठा seq_file *)filp->निजी_data;
	काष्ठा rtw_debugfs_priv *debugfs_priv = seqpriv->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	अक्षर पंचांगp[32 + 1];
	bool enable;
	पूर्णांक ret;

	rtw_debugfs_copy_from_user(पंचांगp, माप(पंचांगp), buffer, count, 1);

	ret = kstrtobool(पंचांगp, &enable);
	अगर (ret) अणु
		rtw_warn(rtwdev, "invalid arguments\n");
		वापस ret;
	पूर्ण

	mutex_lock(&rtwdev->mutex);
	coex->manual_control = !enable;
	mutex_unlock(&rtwdev->mutex);

	वापस count;
पूर्ण

अटल पूर्णांक rtw_debugfs_get_coex_enable(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	काष्ठा rtw_coex *coex = &rtwdev->coex;

	seq_म_लिखो(m, "coex mechanism %s\n",
		   coex->manual_control ? "disabled" : "enabled");

	वापस 0;
पूर्ण

अटल sमाप_प्रकार rtw_debugfs_set_fw_crash(काष्ठा file *filp,
					स्थिर अक्षर __user *buffer,
					माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा seq_file *seqpriv = (काष्ठा seq_file *)filp->निजी_data;
	काष्ठा rtw_debugfs_priv *debugfs_priv = seqpriv->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	अक्षर पंचांगp[32 + 1];
	bool input;
	पूर्णांक ret;

	rtw_debugfs_copy_from_user(पंचांगp, माप(पंचांगp), buffer, count, 1);

	ret = kstrtobool(पंचांगp, &input);
	अगर (ret)
		वापस -EINVAL;

	अगर (!input)
		वापस -EINVAL;

	rtw_ग_लिखो8(rtwdev, REG_HRCV_MSG, 1);

	वापस count;
पूर्ण

अटल पूर्णांक rtw_debugfs_get_fw_crash(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;

	seq_म_लिखो(m, "%d\n", test_bit(RTW_FLAG_RESTARTING, rtwdev->flags));
	वापस 0;
पूर्ण

अटल sमाप_प्रकार rtw_debugfs_set_dm_cap(काष्ठा file *filp,
				      स्थिर अक्षर __user *buffer,
				      माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा seq_file *seqpriv = (काष्ठा seq_file *)filp->निजी_data;
	काष्ठा rtw_debugfs_priv *debugfs_priv = seqpriv->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	पूर्णांक bit;
	bool en;

	अगर (kstrtoपूर्णांक_from_user(buffer, count, 10, &bit))
		वापस -EINVAL;

	en = bit > 0;
	bit = असल(bit);

	अगर (bit >= RTW_DM_CAP_NUM) अणु
		rtw_warn(rtwdev, "unknown DM CAP %d\n", bit);
		वापस -EINVAL;
	पूर्ण

	अगर (en)
		dm_info->dm_flags &= ~BIT(bit);
	अन्यथा
		dm_info->dm_flags |= BIT(bit);

	debugfs_priv->dm_cap.bit = bit;

	वापस count;
पूर्ण

अटल व्योम dump_gapk_status(काष्ठा rtw_dev *rtwdev, काष्ठा seq_file *m)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_gapk_info *txgapk = &rtwdev->dm_info.gapk;
	पूर्णांक i, path;
	u32 val;

	seq_म_लिखो(m, "\n(%2d) %c%s\n\n", RTW_DM_CAP_TXGAPK,
		   dm_info->dm_flags & BIT(RTW_DM_CAP_TXGAPK) ? '-' : '+',
		   rtw_dm_cap_strs[RTW_DM_CAP_TXGAPK]);

	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
		val = rtw_पढ़ो_rf(rtwdev, path, RF_GAINTX, RFREG_MASK);
		seq_म_लिखो(m, "path %d:\n0x%x = 0x%x\n", path, RF_GAINTX, val);

		क्रम (i = 0; i < RF_HW_OFFSET_NUM; i++)
			seq_म_लिखो(m, "[TXGAPK] offset %d %d\n",
				   txgapk->rf3f_fs[path][i], i);
		seq_माला_दो(m, "\n");
	पूर्ण
पूर्ण

अटल पूर्णांक rtw_debugfs_get_dm_cap(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtw_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtw_dev *rtwdev = debugfs_priv->rtwdev;
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	पूर्णांक i;

	चयन (debugfs_priv->dm_cap.bit) अणु
	हाल RTW_DM_CAP_TXGAPK:
		dump_gapk_status(rtwdev, m);
		अवरोध;
	शेष:
		क्रम (i = 1; i < RTW_DM_CAP_NUM; i++) अणु
			seq_म_लिखो(m, "(%2d) %c%s\n", i,
				   dm_info->dm_flags & BIT(i) ? '-' : '+',
				   rtw_dm_cap_strs[i]);
		पूर्ण
		अवरोध;
	पूर्ण
	debugfs_priv->dm_cap.bit = RTW_DM_CAP_NA;
	वापस 0;
पूर्ण

#घोषणा rtw_debug_impl_mac(page, addr)				\
अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_mac_ ##page = अणु	\
	.cb_पढ़ो = rtw_debug_get_mac_page,			\
	.cb_data = addr,					\
पूर्ण

rtw_debug_impl_mac(0, 0x0000);
rtw_debug_impl_mac(1, 0x0100);
rtw_debug_impl_mac(2, 0x0200);
rtw_debug_impl_mac(3, 0x0300);
rtw_debug_impl_mac(4, 0x0400);
rtw_debug_impl_mac(5, 0x0500);
rtw_debug_impl_mac(6, 0x0600);
rtw_debug_impl_mac(7, 0x0700);
rtw_debug_impl_mac(10, 0x1000);
rtw_debug_impl_mac(11, 0x1100);
rtw_debug_impl_mac(12, 0x1200);
rtw_debug_impl_mac(13, 0x1300);
rtw_debug_impl_mac(14, 0x1400);
rtw_debug_impl_mac(15, 0x1500);
rtw_debug_impl_mac(16, 0x1600);
rtw_debug_impl_mac(17, 0x1700);

#घोषणा rtw_debug_impl_bb(page, addr)			\
अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_bb_ ##page = अणु	\
	.cb_पढ़ो = rtw_debug_get_bb_page,			\
	.cb_data = addr,					\
पूर्ण

rtw_debug_impl_bb(8, 0x0800);
rtw_debug_impl_bb(9, 0x0900);
rtw_debug_impl_bb(a, 0x0a00);
rtw_debug_impl_bb(b, 0x0b00);
rtw_debug_impl_bb(c, 0x0c00);
rtw_debug_impl_bb(d, 0x0d00);
rtw_debug_impl_bb(e, 0x0e00);
rtw_debug_impl_bb(f, 0x0f00);
rtw_debug_impl_bb(18, 0x1800);
rtw_debug_impl_bb(19, 0x1900);
rtw_debug_impl_bb(1a, 0x1a00);
rtw_debug_impl_bb(1b, 0x1b00);
rtw_debug_impl_bb(1c, 0x1c00);
rtw_debug_impl_bb(1d, 0x1d00);
rtw_debug_impl_bb(1e, 0x1e00);
rtw_debug_impl_bb(1f, 0x1f00);
rtw_debug_impl_bb(2c, 0x2c00);
rtw_debug_impl_bb(2d, 0x2d00);
rtw_debug_impl_bb(40, 0x4000);
rtw_debug_impl_bb(41, 0x4100);

अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_rf_dump = अणु
	.cb_पढ़ो = rtw_debug_get_rf_dump,
पूर्ण;

अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_tx_pwr_tbl = अणु
	.cb_पढ़ो = rtw_debugfs_get_tx_pwr_tbl,
पूर्ण;

अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_ग_लिखो_reg = अणु
	.cb_ग_लिखो = rtw_debugfs_set_ग_लिखो_reg,
पूर्ण;

अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_h2c = अणु
	.cb_ग_लिखो = rtw_debugfs_set_h2c,
पूर्ण;

अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_rf_ग_लिखो = अणु
	.cb_ग_लिखो = rtw_debugfs_set_rf_ग_लिखो,
पूर्ण;

अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_rf_पढ़ो = अणु
	.cb_ग_लिखो = rtw_debugfs_set_rf_पढ़ो,
	.cb_पढ़ो = rtw_debugfs_get_rf_पढ़ो,
पूर्ण;

अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_पढ़ो_reg = अणु
	.cb_ग_लिखो = rtw_debugfs_set_पढ़ो_reg,
	.cb_पढ़ो = rtw_debugfs_get_पढ़ो_reg,
पूर्ण;

अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_dump_cam = अणु
	.cb_ग_लिखो = rtw_debugfs_set_single_input,
	.cb_पढ़ो = rtw_debugfs_get_dump_cam,
पूर्ण;

अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_rsvd_page = अणु
	.cb_ग_लिखो = rtw_debugfs_set_rsvd_page,
	.cb_पढ़ो = rtw_debugfs_get_rsvd_page,
पूर्ण;

अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_phy_info = अणु
	.cb_पढ़ो = rtw_debugfs_get_phy_info,
पूर्ण;

अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_coex_enable = अणु
	.cb_ग_लिखो = rtw_debugfs_set_coex_enable,
	.cb_पढ़ो = rtw_debugfs_get_coex_enable,
पूर्ण;

अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_coex_info = अणु
	.cb_पढ़ो = rtw_debugfs_get_coex_info,
पूर्ण;

अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_fw_crash = अणु
	.cb_ग_लिखो = rtw_debugfs_set_fw_crash,
	.cb_पढ़ो = rtw_debugfs_get_fw_crash,
पूर्ण;

अटल काष्ठा rtw_debugfs_priv rtw_debug_priv_dm_cap = अणु
	.cb_ग_लिखो = rtw_debugfs_set_dm_cap,
	.cb_पढ़ो = rtw_debugfs_get_dm_cap,
पूर्ण;

#घोषणा rtw_debugfs_add_core(name, mode, fopname, parent)		\
	करो अणु								\
		rtw_debug_priv_ ##name.rtwdev = rtwdev;			\
		अगर (!debugfs_create_file(#name, mode,			\
					 parent, &rtw_debug_priv_ ##name,\
					 &file_ops_ ##fopname))		\
			pr_debug("Unable to initialize debugfs:%s\n",	\
			       #name);					\
	पूर्ण जबतक (0)

#घोषणा rtw_debugfs_add_w(name)						\
	rtw_debugfs_add_core(name, S_IFREG | 0222, common_ग_लिखो, debugfs_topdir)
#घोषणा rtw_debugfs_add_rw(name)					\
	rtw_debugfs_add_core(name, S_IFREG | 0666, single_rw, debugfs_topdir)
#घोषणा rtw_debugfs_add_r(name)						\
	rtw_debugfs_add_core(name, S_IFREG | 0444, single_r, debugfs_topdir)

व्योम rtw_debugfs_init(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा dentry *debugfs_topdir;

	debugfs_topdir = debugfs_create_dir("rtw88",
					    rtwdev->hw->wiphy->debugfsdir);
	rtw_debugfs_add_w(ग_लिखो_reg);
	rtw_debugfs_add_rw(पढ़ो_reg);
	rtw_debugfs_add_w(rf_ग_लिखो);
	rtw_debugfs_add_rw(rf_पढ़ो);
	rtw_debugfs_add_rw(dump_cam);
	rtw_debugfs_add_rw(rsvd_page);
	rtw_debugfs_add_r(phy_info);
	rtw_debugfs_add_r(coex_info);
	rtw_debugfs_add_rw(coex_enable);
	rtw_debugfs_add_w(h2c);
	rtw_debugfs_add_r(mac_0);
	rtw_debugfs_add_r(mac_1);
	rtw_debugfs_add_r(mac_2);
	rtw_debugfs_add_r(mac_3);
	rtw_debugfs_add_r(mac_4);
	rtw_debugfs_add_r(mac_5);
	rtw_debugfs_add_r(mac_6);
	rtw_debugfs_add_r(mac_7);
	rtw_debugfs_add_r(bb_8);
	rtw_debugfs_add_r(bb_9);
	rtw_debugfs_add_r(bb_a);
	rtw_debugfs_add_r(bb_b);
	rtw_debugfs_add_r(bb_c);
	rtw_debugfs_add_r(bb_d);
	rtw_debugfs_add_r(bb_e);
	rtw_debugfs_add_r(bb_f);
	rtw_debugfs_add_r(mac_10);
	rtw_debugfs_add_r(mac_11);
	rtw_debugfs_add_r(mac_12);
	rtw_debugfs_add_r(mac_13);
	rtw_debugfs_add_r(mac_14);
	rtw_debugfs_add_r(mac_15);
	rtw_debugfs_add_r(mac_16);
	rtw_debugfs_add_r(mac_17);
	rtw_debugfs_add_r(bb_18);
	rtw_debugfs_add_r(bb_19);
	rtw_debugfs_add_r(bb_1a);
	rtw_debugfs_add_r(bb_1b);
	rtw_debugfs_add_r(bb_1c);
	rtw_debugfs_add_r(bb_1d);
	rtw_debugfs_add_r(bb_1e);
	rtw_debugfs_add_r(bb_1f);
	अगर (rtwdev->chip->id == RTW_CHIP_TYPE_8822C) अणु
		rtw_debugfs_add_r(bb_2c);
		rtw_debugfs_add_r(bb_2d);
		rtw_debugfs_add_r(bb_40);
		rtw_debugfs_add_r(bb_41);
	पूर्ण
	rtw_debugfs_add_r(rf_dump);
	rtw_debugfs_add_r(tx_pwr_tbl);
	rtw_debugfs_add_rw(fw_crash);
	rtw_debugfs_add_rw(dm_cap);
पूर्ण

#पूर्ण_अगर /* CONFIG_RTW88_DEBUGFS */

#अगर_घोषित CONFIG_RTW88_DEBUG

व्योम __rtw_dbg(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_debug_mask mask,
	       स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf = अणु
		.fmt = fmt,
	पूर्ण;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.va = &args;

	अगर (rtw_debug_mask & mask)
		dev_prपूर्णांकk(KERN_DEBUG, rtwdev->dev, "%pV", &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(__rtw_dbg);

#पूर्ण_अगर /* CONFIG_RTW88_DEBUG */
