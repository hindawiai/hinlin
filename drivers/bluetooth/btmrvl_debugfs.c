<शैली गुरु>
/**
 * Marvell Bluetooth driver: debugfs related functions
 *
 * Copyright (C) 2009, Marvell International Ltd.
 *
 * This software file (the "File") is distributed by Marvell International
 * Ltd. under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 **/

#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "btmrvl_drv.h"

काष्ठा bपंचांगrvl_debugfs_data अणु
	काष्ठा dentry *config_dir;
	काष्ठा dentry *status_dir;
पूर्ण;

अटल sमाप_प्रकार bपंचांगrvl_hscfgcmd_ग_लिखो(काष्ठा file *file,
			स्थिर अक्षर __user *ubuf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा bपंचांगrvl_निजी *priv = file->निजी_data;
	दीर्घ result, ret;

	ret = kम_से_दीर्घ_from_user(ubuf, count, 10, &result);
	अगर (ret)
		वापस ret;

	priv->bपंचांगrvl_dev.hscfgcmd = result;

	अगर (priv->bपंचांगrvl_dev.hscfgcmd) अणु
		bपंचांगrvl_prepare_command(priv);
		wake_up_पूर्णांकerruptible(&priv->मुख्य_thपढ़ो.रुको_q);
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार bपंचांगrvl_hscfgcmd_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा bपंचांगrvl_निजी *priv = file->निजी_data;
	अक्षर buf[16];
	पूर्णांक ret;

	ret = snम_लिखो(buf, माप(buf) - 1, "%d\n",
						priv->bपंचांगrvl_dev.hscfgcmd);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, ret);
पूर्ण

अटल स्थिर काष्ठा file_operations bपंचांगrvl_hscfgcmd_fops = अणु
	.पढ़ो	= bपंचांगrvl_hscfgcmd_पढ़ो,
	.ग_लिखो	= bपंचांगrvl_hscfgcmd_ग_लिखो,
	.खोलो	= simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार bपंचांगrvl_pscmd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा bपंचांगrvl_निजी *priv = file->निजी_data;
	दीर्घ result, ret;

	ret = kम_से_दीर्घ_from_user(ubuf, count, 10, &result);
	अगर (ret)
		वापस ret;

	priv->bपंचांगrvl_dev.pscmd = result;

	अगर (priv->bपंचांगrvl_dev.pscmd) अणु
		bपंचांगrvl_prepare_command(priv);
		wake_up_पूर्णांकerruptible(&priv->मुख्य_thपढ़ो.रुको_q);
	पूर्ण

	वापस count;

पूर्ण

अटल sमाप_प्रकार bपंचांगrvl_pscmd_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा bपंचांगrvl_निजी *priv = file->निजी_data;
	अक्षर buf[16];
	पूर्णांक ret;

	ret = snम_लिखो(buf, माप(buf) - 1, "%d\n", priv->bपंचांगrvl_dev.pscmd);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, ret);
पूर्ण

अटल स्थिर काष्ठा file_operations bपंचांगrvl_pscmd_fops = अणु
	.पढ़ो = bपंचांगrvl_pscmd_पढ़ो,
	.ग_लिखो = bपंचांगrvl_pscmd_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार bपंचांगrvl_hscmd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा bपंचांगrvl_निजी *priv = file->निजी_data;
	दीर्घ result, ret;

	ret = kम_से_दीर्घ_from_user(ubuf, count, 10, &result);
	अगर (ret)
		वापस ret;

	priv->bपंचांगrvl_dev.hscmd = result;
	अगर (priv->bपंचांगrvl_dev.hscmd) अणु
		bपंचांगrvl_prepare_command(priv);
		wake_up_पूर्णांकerruptible(&priv->मुख्य_thपढ़ो.रुको_q);
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार bपंचांगrvl_hscmd_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा bपंचांगrvl_निजी *priv = file->निजी_data;
	अक्षर buf[16];
	पूर्णांक ret;

	ret = snम_लिखो(buf, माप(buf) - 1, "%d\n", priv->bपंचांगrvl_dev.hscmd);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, ret);
पूर्ण

अटल स्थिर काष्ठा file_operations bपंचांगrvl_hscmd_fops = अणु
	.पढ़ो	= bपंचांगrvl_hscmd_पढ़ो,
	.ग_लिखो	= bपंचांगrvl_hscmd_ग_लिखो,
	.खोलो	= simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

व्योम bपंचांगrvl_debugfs_init(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगrvl_निजी *priv = hci_get_drvdata(hdev);
	काष्ठा bपंचांगrvl_debugfs_data *dbg;

	अगर (!hdev->debugfs)
		वापस;

	dbg = kzalloc(माप(*dbg), GFP_KERNEL);
	priv->debugfs_data = dbg;

	अगर (!dbg) अणु
		BT_ERR("Can not allocate memory for btmrvl_debugfs_data.");
		वापस;
	पूर्ण

	dbg->config_dir = debugfs_create_dir("config", hdev->debugfs);

	debugfs_create_u8("psmode", 0644, dbg->config_dir,
			  &priv->bपंचांगrvl_dev.psmode);
	debugfs_create_file("pscmd", 0644, dbg->config_dir,
			    priv, &bपंचांगrvl_pscmd_fops);
	debugfs_create_x16("gpiogap", 0644, dbg->config_dir,
			   &priv->bपंचांगrvl_dev.gpio_gap);
	debugfs_create_u8("hsmode", 0644, dbg->config_dir,
			  &priv->bपंचांगrvl_dev.hsmode);
	debugfs_create_file("hscmd", 0644, dbg->config_dir,
			    priv, &bपंचांगrvl_hscmd_fops);
	debugfs_create_file("hscfgcmd", 0644, dbg->config_dir,
			    priv, &bपंचांगrvl_hscfgcmd_fops);

	dbg->status_dir = debugfs_create_dir("status", hdev->debugfs);
	debugfs_create_u8("curpsmode", 0444, dbg->status_dir,
			  &priv->adapter->psmode);
	debugfs_create_u8("psstate", 0444, dbg->status_dir,
			  &priv->adapter->ps_state);
	debugfs_create_u8("hsstate", 0444, dbg->status_dir,
			  &priv->adapter->hs_state);
	debugfs_create_u8("txdnldready", 0444, dbg->status_dir,
			  &priv->bपंचांगrvl_dev.tx_dnld_rdy);
पूर्ण

व्योम bपंचांगrvl_debugfs_हटाओ(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bपंचांगrvl_निजी *priv = hci_get_drvdata(hdev);
	काष्ठा bपंचांगrvl_debugfs_data *dbg = priv->debugfs_data;

	अगर (!dbg)
		वापस;

	debugfs_हटाओ_recursive(dbg->config_dir);
	debugfs_हटाओ_recursive(dbg->status_dir);

	kमुक्त(dbg);
पूर्ण
