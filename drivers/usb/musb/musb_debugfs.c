<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MUSB OTG driver debugfs support
 *
 * Copyright 2010 Nokia Corporation
 * Contact: Felipe Balbi <felipe.balbi@nokia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/uaccess.h>

#समावेश "musb_core.h"
#समावेश "musb_debug.h"

काष्ठा musb_रेजिस्टर_map अणु
	अक्षर			*name;
	अचिन्हित		offset;
	अचिन्हित		size;
पूर्ण;

अटल स्थिर काष्ठा musb_रेजिस्टर_map musb_regmap[] = अणु
	अणु "FAddr",	MUSB_FADDR,	8 पूर्ण,
	अणु "Power",	MUSB_POWER,	8 पूर्ण,
	अणु "Frame",	MUSB_FRAME,	16 पूर्ण,
	अणु "Index",	MUSB_INDEX,	8 पूर्ण,
	अणु "Testmode",	MUSB_TESTMODE,	8 पूर्ण,
	अणु "TxMaxPp",	MUSB_TXMAXP,	16 पूर्ण,
	अणु "TxCSRp",	MUSB_TXCSR,	16 पूर्ण,
	अणु "RxMaxPp",	MUSB_RXMAXP,	16 पूर्ण,
	अणु "RxCSR",	MUSB_RXCSR,	16 पूर्ण,
	अणु "RxCount",	MUSB_RXCOUNT,	16 पूर्ण,
	अणु "IntrRxE",	MUSB_INTRRXE,	16 पूर्ण,
	अणु "IntrTxE",	MUSB_INTRTXE,	16 पूर्ण,
	अणु "IntrUsbE",	MUSB_INTRUSBE,	8 पूर्ण,
	अणु "DevCtl",	MUSB_DEVCTL,	8 पूर्ण,
	अणु "VControl",	0x68,		32 पूर्ण,
	अणु "HWVers",	0x69,		16 पूर्ण,
	अणु "LinkInfo",	MUSB_LINKINFO,	8 पूर्ण,
	अणु "VPLen",	MUSB_VPLEN,	8 पूर्ण,
	अणु "HS_EOF1",	MUSB_HS_खातापूर्ण1,	8 पूर्ण,
	अणु "FS_EOF1",	MUSB_FS_खातापूर्ण1,	8 पूर्ण,
	अणु "LS_EOF1",	MUSB_LS_खातापूर्ण1,	8 पूर्ण,
	अणु "SOFT_RST",	0x7F,		8 पूर्ण,
	अणु "DMA_CNTLch0",	0x204,	16 पूर्ण,
	अणु "DMA_ADDRch0",	0x208,	32 पूर्ण,
	अणु "DMA_COUNTch0",	0x20C,	32 पूर्ण,
	अणु "DMA_CNTLch1",	0x214,	16 पूर्ण,
	अणु "DMA_ADDRch1",	0x218,	32 पूर्ण,
	अणु "DMA_COUNTch1",	0x21C,	32 पूर्ण,
	अणु "DMA_CNTLch2",	0x224,	16 पूर्ण,
	अणु "DMA_ADDRch2",	0x228,	32 पूर्ण,
	अणु "DMA_COUNTch2",	0x22C,	32 पूर्ण,
	अणु "DMA_CNTLch3",	0x234,	16 पूर्ण,
	अणु "DMA_ADDRch3",	0x238,	32 पूर्ण,
	अणु "DMA_COUNTch3",	0x23C,	32 पूर्ण,
	अणु "DMA_CNTLch4",	0x244,	16 पूर्ण,
	अणु "DMA_ADDRch4",	0x248,	32 पूर्ण,
	अणु "DMA_COUNTch4",	0x24C,	32 पूर्ण,
	अणु "DMA_CNTLch5",	0x254,	16 पूर्ण,
	अणु "DMA_ADDRch5",	0x258,	32 पूर्ण,
	अणु "DMA_COUNTch5",	0x25C,	32 पूर्ण,
	अणु "DMA_CNTLch6",	0x264,	16 पूर्ण,
	अणु "DMA_ADDRch6",	0x268,	32 पूर्ण,
	अणु "DMA_COUNTch6",	0x26C,	32 पूर्ण,
	अणु "DMA_CNTLch7",	0x274,	16 पूर्ण,
	अणु "DMA_ADDRch7",	0x278,	32 पूर्ण,
	अणु "DMA_COUNTch7",	0x27C,	32 पूर्ण,
	अणु "ConfigData",	MUSB_CONFIGDATA,8 पूर्ण,
	अणु "BabbleCtl",	MUSB_BABBLE_CTL,8 पूर्ण,
	अणु "TxFIFOsz",	MUSB_TXFIFOSZ,	8 पूर्ण,
	अणु "RxFIFOsz",	MUSB_RXFIFOSZ,	8 पूर्ण,
	अणु "TxFIFOadd",	MUSB_TXFIFOADD,	16 पूर्ण,
	अणु "RxFIFOadd",	MUSB_RXFIFOADD,	16 पूर्ण,
	अणु "EPInfo",	MUSB_EPINFO,	8 पूर्ण,
	अणु "RAMInfo",	MUSB_RAMINFO,	8 पूर्ण,
	अणु  पूर्ण	/* Terminating Entry */
पूर्ण;

अटल पूर्णांक musb_regdump_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा musb		*musb = s->निजी;
	अचिन्हित		i;

	seq_म_लिखो(s, "MUSB (M)HDRC Register Dump\n");
	pm_runसमय_get_sync(musb->controller);

	क्रम (i = 0; i < ARRAY_SIZE(musb_regmap); i++) अणु
		चयन (musb_regmap[i].size) अणु
		हाल 8:
			seq_म_लिखो(s, "%-12s: %02x\n", musb_regmap[i].name,
					musb_पढ़ोb(musb->mregs, musb_regmap[i].offset));
			अवरोध;
		हाल 16:
			seq_म_लिखो(s, "%-12s: %04x\n", musb_regmap[i].name,
					musb_पढ़ोw(musb->mregs, musb_regmap[i].offset));
			अवरोध;
		हाल 32:
			seq_म_लिखो(s, "%-12s: %08x\n", musb_regmap[i].name,
					musb_पढ़ोl(musb->mregs, musb_regmap[i].offset));
			अवरोध;
		पूर्ण
	पूर्ण

	pm_runसमय_mark_last_busy(musb->controller);
	pm_runसमय_put_स्वतःsuspend(musb->controller);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(musb_regdump);

अटल पूर्णांक musb_test_mode_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा musb		*musb = s->निजी;
	अचिन्हित		test;

	pm_runसमय_get_sync(musb->controller);
	test = musb_पढ़ोb(musb->mregs, MUSB_TESTMODE);
	pm_runसमय_mark_last_busy(musb->controller);
	pm_runसमय_put_स्वतःsuspend(musb->controller);

	अगर (test == (MUSB_TEST_FORCE_HOST | MUSB_TEST_FORCE_FS))
		seq_म_लिखो(s, "force host full-speed\n");

	अन्यथा अगर (test == (MUSB_TEST_FORCE_HOST | MUSB_TEST_FORCE_HS))
		seq_म_लिखो(s, "force host high-speed\n");

	अन्यथा अगर (test == MUSB_TEST_FORCE_HOST)
		seq_म_लिखो(s, "force host\n");

	अन्यथा अगर (test == MUSB_TEST_FIFO_ACCESS)
		seq_म_लिखो(s, "fifo access\n");

	अन्यथा अगर (test == MUSB_TEST_FORCE_FS)
		seq_म_लिखो(s, "force full-speed\n");

	अन्यथा अगर (test == MUSB_TEST_FORCE_HS)
		seq_म_लिखो(s, "force high-speed\n");

	अन्यथा अगर (test == MUSB_TEST_PACKET)
		seq_म_लिखो(s, "test packet\n");

	अन्यथा अगर (test == MUSB_TEST_K)
		seq_म_लिखो(s, "test K\n");

	अन्यथा अगर (test == MUSB_TEST_J)
		seq_म_लिखो(s, "test J\n");

	अन्यथा अगर (test == MUSB_TEST_SE0_NAK)
		seq_म_लिखो(s, "test SE0 NAK\n");

	वापस 0;
पूर्ण

अटल पूर्णांक musb_test_mode_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, musb_test_mode_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार musb_test_mode_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *ubuf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file		*s = file->निजी_data;
	काष्ठा musb		*musb = s->निजी;
	u8			test;
	अक्षर			buf[24];

	स_रखो(buf, 0x00, माप(buf));

	अगर (copy_from_user(buf, ubuf, min_t(माप_प्रकार, माप(buf) - 1, count)))
		वापस -EFAULT;

	pm_runसमय_get_sync(musb->controller);
	test = musb_पढ़ोb(musb->mregs, MUSB_TESTMODE);
	अगर (test) अणु
		dev_err(musb->controller, "Error: test mode is already set. "
			"Please do USB Bus Reset to start a new test.\n");
		जाओ ret;
	पूर्ण

	अगर (strstarts(buf, "force host full-speed"))
		test = MUSB_TEST_FORCE_HOST | MUSB_TEST_FORCE_FS;

	अन्यथा अगर (strstarts(buf, "force host high-speed"))
		test = MUSB_TEST_FORCE_HOST | MUSB_TEST_FORCE_HS;

	अन्यथा अगर (strstarts(buf, "force host"))
		test = MUSB_TEST_FORCE_HOST;

	अन्यथा अगर (strstarts(buf, "fifo access"))
		test = MUSB_TEST_FIFO_ACCESS;

	अन्यथा अगर (strstarts(buf, "force full-speed"))
		test = MUSB_TEST_FORCE_FS;

	अन्यथा अगर (strstarts(buf, "force high-speed"))
		test = MUSB_TEST_FORCE_HS;

	अन्यथा अगर (strstarts(buf, "test packet")) अणु
		test = MUSB_TEST_PACKET;
		musb_load_testpacket(musb);
	पूर्ण

	अन्यथा अगर (strstarts(buf, "test K"))
		test = MUSB_TEST_K;

	अन्यथा अगर (strstarts(buf, "test J"))
		test = MUSB_TEST_J;

	अन्यथा अगर (strstarts(buf, "test SE0 NAK"))
		test = MUSB_TEST_SE0_NAK;

	musb_ग_लिखोb(musb->mregs, MUSB_TESTMODE, test);

ret:
	pm_runसमय_mark_last_busy(musb->controller);
	pm_runसमय_put_स्वतःsuspend(musb->controller);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations musb_test_mode_fops = अणु
	.खोलो			= musb_test_mode_खोलो,
	.ग_लिखो			= musb_test_mode_ग_लिखो,
	.पढ़ो			= seq_पढ़ो,
	.llseek			= seq_lseek,
	.release		= single_release,
पूर्ण;

अटल पूर्णांक musb_softconnect_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा musb	*musb = s->निजी;
	u8		reg;
	पूर्णांक		connect;

	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_A_HOST:
	हाल OTG_STATE_A_WAIT_BCON:
		pm_runसमय_get_sync(musb->controller);

		reg = musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);
		connect = reg & MUSB_DEVCTL_SESSION ? 1 : 0;

		pm_runसमय_mark_last_busy(musb->controller);
		pm_runसमय_put_स्वतःsuspend(musb->controller);
		अवरोध;
	शेष:
		connect = -1;
	पूर्ण

	seq_म_लिखो(s, "%d\n", connect);

	वापस 0;
पूर्ण

अटल पूर्णांक musb_softconnect_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, musb_softconnect_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार musb_softconnect_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *ubuf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file		*s = file->निजी_data;
	काष्ठा musb		*musb = s->निजी;
	अक्षर			buf[2];
	u8			reg;

	स_रखो(buf, 0x00, माप(buf));

	अगर (copy_from_user(&buf, ubuf, min_t(माप_प्रकार, माप(buf) - 1, count)))
		वापस -EFAULT;

	pm_runसमय_get_sync(musb->controller);
	अगर (!म_भेदन(buf, "0", 1)) अणु
		चयन (musb->xceiv->otg->state) अणु
		हाल OTG_STATE_A_HOST:
			musb_root_disconnect(musb);
			reg = musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);
			reg &= ~MUSB_DEVCTL_SESSION;
			musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, reg);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "1", 1)) अणु
		चयन (musb->xceiv->otg->state) अणु
		हाल OTG_STATE_A_WAIT_BCON:
			/*
			 * musb_save_context() called in musb_runसमय_suspend()
			 * might cache devctl with SESSION bit cleared during
			 * soft-disconnect, so specअगरically set SESSION bit
			 * here to preserve it क्रम musb_runसमय_resume().
			 */
			musb->context.devctl |= MUSB_DEVCTL_SESSION;
			reg = musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);
			reg |= MUSB_DEVCTL_SESSION;
			musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, reg);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	pm_runसमय_mark_last_busy(musb->controller);
	pm_runसमय_put_स्वतःsuspend(musb->controller);
	वापस count;
पूर्ण

/*
 * In host mode, connect/disconnect the bus without physically
 * हटाओ the devices.
 */
अटल स्थिर काष्ठा file_operations musb_softconnect_fops = अणु
	.खोलो			= musb_softconnect_खोलो,
	.ग_लिखो			= musb_softconnect_ग_लिखो,
	.पढ़ो			= seq_पढ़ो,
	.llseek			= seq_lseek,
	.release		= single_release,
पूर्ण;

व्योम musb_init_debugfs(काष्ठा musb *musb)
अणु
	काष्ठा dentry *root;

	root = debugfs_create_dir(dev_name(musb->controller), usb_debug_root);
	musb->debugfs_root = root;

	debugfs_create_file("regdump", S_IRUGO, root, musb, &musb_regdump_fops);
	debugfs_create_file("testmode", S_IRUGO | S_IWUSR, root, musb,
			    &musb_test_mode_fops);
	debugfs_create_file("softconnect", S_IRUGO | S_IWUSR, root, musb,
			    &musb_softconnect_fops);
पूर्ण

व्योम /* __init_or_निकास */ musb_निकास_debugfs(काष्ठा musb *musb)
अणु
	debugfs_हटाओ_recursive(musb->debugfs_root);
पूर्ण
