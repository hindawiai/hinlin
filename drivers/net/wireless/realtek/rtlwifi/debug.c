<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "wifi.h"
#समावेश "cam.h"

#समावेश <linux/moduleparam.h>
#समावेश <linux/vदो_स्मृति.h>

#अगर_घोषित CONFIG_RTLWIFI_DEBUG
व्योम _rtl_dbg_prपूर्णांक(काष्ठा rtl_priv *rtlpriv, u64 comp, पूर्णांक level,
		    स्थिर अक्षर *fmt, ...)
अणु
	अगर (unlikely((comp & rtlpriv->cfg->mod_params->debug_mask) &&
		     level <= rtlpriv->cfg->mod_params->debug_level)) अणु
		काष्ठा va_क्रमmat vaf;
		बहु_सूची args;

		बहु_शुरू(args, fmt);

		vaf.fmt = fmt;
		vaf.va = &args;

		pr_info("%pV", &vaf);

		बहु_पूर्ण(args);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(_rtl_dbg_prपूर्णांक);

व्योम _rtl_dbg_prपूर्णांक_data(काष्ठा rtl_priv *rtlpriv, u64 comp, पूर्णांक level,
			 स्थिर अक्षर *titlestring,
			 स्थिर व्योम *hexdata, पूर्णांक hexdatalen)
अणु
	अगर (unlikely(((comp) & rtlpriv->cfg->mod_params->debug_mask) &&
		     ((level) <= rtlpriv->cfg->mod_params->debug_level))) अणु
		pr_info("In process \"%s\" (pid %i): %s\n",
			current->comm, current->pid, titlestring);
		prपूर्णांक_hex_dump_bytes("", DUMP_PREFIX_NONE,
				     hexdata, hexdatalen);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(_rtl_dbg_prपूर्णांक_data);

काष्ठा rtl_debugfs_priv अणु
	काष्ठा rtl_priv *rtlpriv;
	पूर्णांक (*cb_पढ़ो)(काष्ठा seq_file *m, व्योम *v);
	sमाप_प्रकार (*cb_ग_लिखो)(काष्ठा file *filp, स्थिर अक्षर __user *buffer,
			    माप_प्रकार count, loff_t *loff);
	u32 cb_data;
पूर्ण;

अटल काष्ठा dentry *debugfs_topdir;

अटल पूर्णांक rtl_debug_get_common(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtl_debugfs_priv *debugfs_priv = m->निजी;

	वापस debugfs_priv->cb_पढ़ो(m, v);
पूर्ण

अटल पूर्णांक dl_debug_खोलो_common(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, rtl_debug_get_common, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations file_ops_common = अणु
	.खोलो = dl_debug_खोलो_common,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल पूर्णांक rtl_debug_get_mac_page(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtl_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtl_priv *rtlpriv = debugfs_priv->rtlpriv;
	u32 page = debugfs_priv->cb_data;
	पूर्णांक i, n;
	पूर्णांक max = 0xff;

	क्रम (n = 0; n <= max; ) अणु
		seq_म_लिखो(m, "\n%8.8x  ", n + page);
		क्रम (i = 0; i < 4 && n <= max; i++, n += 4)
			seq_म_लिखो(m, "%8.8x    ",
				   rtl_पढ़ो_dword(rtlpriv, (page | n)));
	पूर्ण
	seq_माला_दो(m, "\n");
	वापस 0;
पूर्ण

#घोषणा RTL_DEBUG_IMPL_MAC_SERIES(page, addr)			\
अटल काष्ठा rtl_debugfs_priv rtl_debug_priv_mac_ ##page = अणु	\
	.cb_पढ़ो = rtl_debug_get_mac_page,			\
	.cb_data = addr,					\
पूर्ण

RTL_DEBUG_IMPL_MAC_SERIES(0, 0x0000);
RTL_DEBUG_IMPL_MAC_SERIES(1, 0x0100);
RTL_DEBUG_IMPL_MAC_SERIES(2, 0x0200);
RTL_DEBUG_IMPL_MAC_SERIES(3, 0x0300);
RTL_DEBUG_IMPL_MAC_SERIES(4, 0x0400);
RTL_DEBUG_IMPL_MAC_SERIES(5, 0x0500);
RTL_DEBUG_IMPL_MAC_SERIES(6, 0x0600);
RTL_DEBUG_IMPL_MAC_SERIES(7, 0x0700);
RTL_DEBUG_IMPL_MAC_SERIES(10, 0x1000);
RTL_DEBUG_IMPL_MAC_SERIES(11, 0x1100);
RTL_DEBUG_IMPL_MAC_SERIES(12, 0x1200);
RTL_DEBUG_IMPL_MAC_SERIES(13, 0x1300);
RTL_DEBUG_IMPL_MAC_SERIES(14, 0x1400);
RTL_DEBUG_IMPL_MAC_SERIES(15, 0x1500);
RTL_DEBUG_IMPL_MAC_SERIES(16, 0x1600);
RTL_DEBUG_IMPL_MAC_SERIES(17, 0x1700);

अटल पूर्णांक rtl_debug_get_bb_page(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtl_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtl_priv *rtlpriv = debugfs_priv->rtlpriv;
	काष्ठा ieee80211_hw *hw = rtlpriv->hw;
	u32 page = debugfs_priv->cb_data;
	पूर्णांक i, n;
	पूर्णांक max = 0xff;

	क्रम (n = 0; n <= max; ) अणु
		seq_म_लिखो(m, "\n%8.8x  ", n + page);
		क्रम (i = 0; i < 4 && n <= max; i++, n += 4)
			seq_म_लिखो(m, "%8.8x    ",
				   rtl_get_bbreg(hw, (page | n), 0xffffffff));
	पूर्ण
	seq_माला_दो(m, "\n");
	वापस 0;
पूर्ण

#घोषणा RTL_DEBUG_IMPL_BB_SERIES(page, addr)			\
अटल काष्ठा rtl_debugfs_priv rtl_debug_priv_bb_ ##page = अणु	\
	.cb_पढ़ो = rtl_debug_get_bb_page,			\
	.cb_data = addr,					\
पूर्ण

RTL_DEBUG_IMPL_BB_SERIES(8, 0x0800);
RTL_DEBUG_IMPL_BB_SERIES(9, 0x0900);
RTL_DEBUG_IMPL_BB_SERIES(a, 0x0a00);
RTL_DEBUG_IMPL_BB_SERIES(b, 0x0b00);
RTL_DEBUG_IMPL_BB_SERIES(c, 0x0c00);
RTL_DEBUG_IMPL_BB_SERIES(d, 0x0d00);
RTL_DEBUG_IMPL_BB_SERIES(e, 0x0e00);
RTL_DEBUG_IMPL_BB_SERIES(f, 0x0f00);
RTL_DEBUG_IMPL_BB_SERIES(18, 0x1800);
RTL_DEBUG_IMPL_BB_SERIES(19, 0x1900);
RTL_DEBUG_IMPL_BB_SERIES(1a, 0x1a00);
RTL_DEBUG_IMPL_BB_SERIES(1b, 0x1b00);
RTL_DEBUG_IMPL_BB_SERIES(1c, 0x1c00);
RTL_DEBUG_IMPL_BB_SERIES(1d, 0x1d00);
RTL_DEBUG_IMPL_BB_SERIES(1e, 0x1e00);
RTL_DEBUG_IMPL_BB_SERIES(1f, 0x1f00);

अटल पूर्णांक rtl_debug_get_reg_rf(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtl_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtl_priv *rtlpriv = debugfs_priv->rtlpriv;
	काष्ठा ieee80211_hw *hw = rtlpriv->hw;
	क्रमागत radio_path rfpath = debugfs_priv->cb_data;
	पूर्णांक i, n;
	पूर्णांक max = 0x40;

	अगर (IS_HARDWARE_TYPE_8822B(rtlpriv))
		max = 0xff;

	seq_म_लिखो(m, "\nPATH(%d)", rfpath);

	क्रम (n = 0; n <= max; ) अणु
		seq_म_लिखो(m, "\n%8.8x  ", n);
		क्रम (i = 0; i < 4 && n <= max; n += 1, i++)
			seq_म_लिखो(m, "%8.8x    ",
				   rtl_get_rfreg(hw, rfpath, n, 0xffffffff));
	पूर्ण
	seq_माला_दो(m, "\n");
	वापस 0;
पूर्ण

#घोषणा RTL_DEBUG_IMPL_RF_SERIES(page, addr)			\
अटल काष्ठा rtl_debugfs_priv rtl_debug_priv_rf_ ##page = अणु	\
	.cb_पढ़ो = rtl_debug_get_reg_rf,			\
	.cb_data = addr,					\
पूर्ण

RTL_DEBUG_IMPL_RF_SERIES(a, RF90_PATH_A);
RTL_DEBUG_IMPL_RF_SERIES(b, RF90_PATH_B);

अटल पूर्णांक rtl_debug_get_cam_रेजिस्टर(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtl_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtl_priv *rtlpriv = debugfs_priv->rtlpriv;
	पूर्णांक start = debugfs_priv->cb_data;
	u32 target_cmd = 0;
	u32 target_val = 0;
	u8 entry_i = 0;
	u32 ulstatus;
	पूर्णांक i = 100, j = 0;
	पूर्णांक end = (start + 11 > TOTAL_CAM_ENTRY ? TOTAL_CAM_ENTRY : start + 11);

	/* This dump the current रेजिस्टर page */
	seq_म_लिखो(m,
		   "\n#################### SECURITY CAM (%d-%d) ##################\n",
		   start, end - 1);

	क्रम (j = start; j < end; j++) अणु
		seq_म_लिखो(m, "\nD:  %2x > ", j);
		क्रम (entry_i = 0; entry_i < CAM_CONTENT_COUNT; entry_i++) अणु
			/* polling bit, and No Write enable, and address  */
			target_cmd = entry_i + CAM_CONTENT_COUNT * j;
			target_cmd = target_cmd | BIT(31);

			/* Check polling bit is clear */
			जबतक ((i--) >= 0) अणु
				ulstatus =
				    rtl_पढ़ो_dword(rtlpriv,
						   rtlpriv->cfg->maps[RWCAM]);
				अगर (ulstatus & BIT(31))
					जारी;
				अन्यथा
					अवरोध;
			पूर्ण

			rtl_ग_लिखो_dword(rtlpriv, rtlpriv->cfg->maps[RWCAM],
					target_cmd);
			target_val = rtl_पढ़ो_dword(rtlpriv,
						    rtlpriv->cfg->maps[RCAMO]);
			seq_म_लिखो(m, "%8.8x ", target_val);
		पूर्ण
	पूर्ण
	seq_माला_दो(m, "\n");
	वापस 0;
पूर्ण

#घोषणा RTL_DEBUG_IMPL_CAM_SERIES(page, addr)			\
अटल काष्ठा rtl_debugfs_priv rtl_debug_priv_cam_ ##page = अणु	\
	.cb_पढ़ो = rtl_debug_get_cam_रेजिस्टर,			\
	.cb_data = addr,					\
पूर्ण

RTL_DEBUG_IMPL_CAM_SERIES(1, 0);
RTL_DEBUG_IMPL_CAM_SERIES(2, 11);
RTL_DEBUG_IMPL_CAM_SERIES(3, 22);

अटल पूर्णांक rtl_debug_get_btcoex(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rtl_debugfs_priv *debugfs_priv = m->निजी;
	काष्ठा rtl_priv *rtlpriv = debugfs_priv->rtlpriv;

	अगर (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_display_bt_coex_info(rtlpriv,
								     m);

	seq_माला_दो(m, "\n");

	वापस 0;
पूर्ण

अटल काष्ठा rtl_debugfs_priv rtl_debug_priv_btcoex = अणु
	.cb_पढ़ो = rtl_debug_get_btcoex,
	.cb_data = 0,
पूर्ण;

अटल sमाप_प्रकार rtl_debugfs_set_ग_लिखो_reg(काष्ठा file *filp,
					 स्थिर अक्षर __user *buffer,
					 माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा rtl_debugfs_priv *debugfs_priv = filp->निजी_data;
	काष्ठा rtl_priv *rtlpriv = debugfs_priv->rtlpriv;
	अक्षर पंचांगp[32 + 1];
	पूर्णांक पंचांगp_len;
	u32 addr, val, len;
	पूर्णांक num;

	अगर (count < 3)
		वापस -EFAULT;

	पंचांगp_len = (count > माप(पंचांगp) - 1 ? माप(पंचांगp) - 1 : count);

	अगर (!buffer || copy_from_user(पंचांगp, buffer, पंचांगp_len))
		वापस count;

	पंचांगp[पंचांगp_len] = '\0';

	/* ग_लिखो BB/MAC रेजिस्टर */
	num = माला_पूछो(पंचांगp, "%x %x %x", &addr, &val, &len);

	अगर (num !=  3)
		वापस count;

	चयन (len) अणु
	हाल 1:
		rtl_ग_लिखो_byte(rtlpriv, addr, (u8)val);
		अवरोध;
	हाल 2:
		rtl_ग_लिखो_word(rtlpriv, addr, (u16)val);
		अवरोध;
	हाल 4:
		rtl_ग_लिखो_dword(rtlpriv, addr, val);
		अवरोध;
	शेष:
		/*prपूर्णांकk("error write length=%d", len);*/
		अवरोध;
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा rtl_debugfs_priv rtl_debug_priv_ग_लिखो_reg = अणु
	.cb_ग_लिखो = rtl_debugfs_set_ग_लिखो_reg,
पूर्ण;

अटल sमाप_प्रकार rtl_debugfs_set_ग_लिखो_h2c(काष्ठा file *filp,
					 स्थिर अक्षर __user *buffer,
					 माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा rtl_debugfs_priv *debugfs_priv = filp->निजी_data;
	काष्ठा rtl_priv *rtlpriv = debugfs_priv->rtlpriv;
	काष्ठा ieee80211_hw *hw = rtlpriv->hw;
	अक्षर पंचांगp[32 + 1];
	पूर्णांक पंचांगp_len;
	u8 h2c_len, h2c_data_packed[8];
	पूर्णांक h2c_data[8];	/* idx 0: cmd */
	पूर्णांक i;

	अगर (count < 3)
		वापस -EFAULT;

	पंचांगp_len = (count > माप(पंचांगp) - 1 ? माप(पंचांगp) - 1 : count);

	अगर (!buffer || copy_from_user(पंचांगp, buffer, पंचांगp_len))
		वापस count;

	पंचांगp[पंचांगp_len] = '\0';

	h2c_len = माला_पूछो(पंचांगp, "%X %X %X %X %X %X %X %X",
			 &h2c_data[0], &h2c_data[1],
			 &h2c_data[2], &h2c_data[3],
			 &h2c_data[4], &h2c_data[5],
			 &h2c_data[6], &h2c_data[7]);

	अगर (h2c_len <= 0)
		वापस count;

	क्रम (i = 0; i < h2c_len; i++)
		h2c_data_packed[i] = (u8)h2c_data[i];

	rtlpriv->cfg->ops->fill_h2c_cmd(hw, h2c_data_packed[0],
					h2c_len - 1,
					&h2c_data_packed[1]);

	वापस count;
पूर्ण

अटल काष्ठा rtl_debugfs_priv rtl_debug_priv_ग_लिखो_h2c = अणु
	.cb_ग_लिखो = rtl_debugfs_set_ग_लिखो_h2c,
पूर्ण;

अटल sमाप_प्रकार rtl_debugfs_set_ग_लिखो_rfreg(काष्ठा file *filp,
					   स्थिर अक्षर __user *buffer,
					    माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा rtl_debugfs_priv *debugfs_priv = filp->निजी_data;
	काष्ठा rtl_priv *rtlpriv = debugfs_priv->rtlpriv;
	काष्ठा ieee80211_hw *hw = rtlpriv->hw;
	अक्षर पंचांगp[32 + 1];
	पूर्णांक पंचांगp_len;
	पूर्णांक num;
	पूर्णांक path;
	u32 addr, biपंचांगask, data;

	अगर (count < 3)
		वापस -EFAULT;

	पंचांगp_len = (count > माप(पंचांगp) - 1 ? माप(पंचांगp) - 1 : count);

	अगर (!buffer || copy_from_user(पंचांगp, buffer, पंचांगp_len))
		वापस count;

	पंचांगp[पंचांगp_len] = '\0';

	num = माला_पूछो(पंचांगp, "%X %X %X %X",
		     &path, &addr, &biपंचांगask, &data);

	अगर (num != 4) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_DMESG,
			"Format is <path> <addr> <mask> <data>\n");
		वापस count;
	पूर्ण

	rtl_set_rfreg(hw, path, addr, biपंचांगask, data);

	वापस count;
पूर्ण

अटल काष्ठा rtl_debugfs_priv rtl_debug_priv_ग_लिखो_rfreg = अणु
	.cb_ग_लिखो = rtl_debugfs_set_ग_लिखो_rfreg,
पूर्ण;

अटल पूर्णांक rtl_debugfs_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार rtl_debugfs_common_ग_लिखो(काष्ठा file *filp,
					स्थिर अक्षर __user *buffer,
					माप_प्रकार count, loff_t *loff)
अणु
	काष्ठा rtl_debugfs_priv *debugfs_priv = filp->निजी_data;

	वापस debugfs_priv->cb_ग_लिखो(filp, buffer, count, loff);
पूर्ण

अटल स्थिर काष्ठा file_operations file_ops_common_ग_लिखो = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = rtl_debugfs_common_ग_लिखो,
	.खोलो = simple_खोलो,
	.release = rtl_debugfs_बंद,
पूर्ण;

#घोषणा RTL_DEBUGFS_ADD_CORE(name, mode, fopname)			   \
	करो अणु								   \
		rtl_debug_priv_ ##name.rtlpriv = rtlpriv;		   \
		debugfs_create_file(#name, mode, parent,		   \
				    &rtl_debug_priv_ ##name,		   \
				    &file_ops_ ##fopname);		   \
	पूर्ण जबतक (0)

#घोषणा RTL_DEBUGFS_ADD(name)						   \
		RTL_DEBUGFS_ADD_CORE(name, S_IFREG | 0444, common)
#घोषणा RTL_DEBUGFS_ADD_W(name)						   \
		RTL_DEBUGFS_ADD_CORE(name, S_IFREG | 0222, common_ग_लिखो)

व्योम rtl_debug_add_one(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा dentry *parent;

	snम_लिखो(rtlpriv->dbg.debugfs_name, 18, "%pMF", rtlefuse->dev_addr);

	rtlpriv->dbg.debugfs_dir =
		debugfs_create_dir(rtlpriv->dbg.debugfs_name, debugfs_topdir);

	parent = rtlpriv->dbg.debugfs_dir;

	RTL_DEBUGFS_ADD(mac_0);
	RTL_DEBUGFS_ADD(mac_1);
	RTL_DEBUGFS_ADD(mac_2);
	RTL_DEBUGFS_ADD(mac_3);
	RTL_DEBUGFS_ADD(mac_4);
	RTL_DEBUGFS_ADD(mac_5);
	RTL_DEBUGFS_ADD(mac_6);
	RTL_DEBUGFS_ADD(mac_7);
	RTL_DEBUGFS_ADD(bb_8);
	RTL_DEBUGFS_ADD(bb_9);
	RTL_DEBUGFS_ADD(bb_a);
	RTL_DEBUGFS_ADD(bb_b);
	RTL_DEBUGFS_ADD(bb_c);
	RTL_DEBUGFS_ADD(bb_d);
	RTL_DEBUGFS_ADD(bb_e);
	RTL_DEBUGFS_ADD(bb_f);
	RTL_DEBUGFS_ADD(mac_10);
	RTL_DEBUGFS_ADD(mac_11);
	RTL_DEBUGFS_ADD(mac_12);
	RTL_DEBUGFS_ADD(mac_13);
	RTL_DEBUGFS_ADD(mac_14);
	RTL_DEBUGFS_ADD(mac_15);
	RTL_DEBUGFS_ADD(mac_16);
	RTL_DEBUGFS_ADD(mac_17);
	RTL_DEBUGFS_ADD(bb_18);
	RTL_DEBUGFS_ADD(bb_19);
	RTL_DEBUGFS_ADD(bb_1a);
	RTL_DEBUGFS_ADD(bb_1b);
	RTL_DEBUGFS_ADD(bb_1c);
	RTL_DEBUGFS_ADD(bb_1d);
	RTL_DEBUGFS_ADD(bb_1e);
	RTL_DEBUGFS_ADD(bb_1f);
	RTL_DEBUGFS_ADD(rf_a);
	RTL_DEBUGFS_ADD(rf_b);

	RTL_DEBUGFS_ADD(cam_1);
	RTL_DEBUGFS_ADD(cam_2);
	RTL_DEBUGFS_ADD(cam_3);

	RTL_DEBUGFS_ADD(btcoex);

	RTL_DEBUGFS_ADD_W(ग_लिखो_reg);
	RTL_DEBUGFS_ADD_W(ग_लिखो_h2c);
	RTL_DEBUGFS_ADD_W(ग_लिखो_rfreg);
पूर्ण
EXPORT_SYMBOL_GPL(rtl_debug_add_one);

व्योम rtl_debug_हटाओ_one(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	debugfs_हटाओ_recursive(rtlpriv->dbg.debugfs_dir);
	rtlpriv->dbg.debugfs_dir = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(rtl_debug_हटाओ_one);

व्योम rtl_debugfs_add_topdir(व्योम)
अणु
	debugfs_topdir = debugfs_create_dir("rtlwifi", शून्य);
पूर्ण

व्योम rtl_debugfs_हटाओ_topdir(व्योम)
अणु
	debugfs_हटाओ_recursive(debugfs_topdir);
पूर्ण

#पूर्ण_अगर
