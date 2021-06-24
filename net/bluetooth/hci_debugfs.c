<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux

   Copyright (C) 2014 Intel Corporation

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

#समावेश <linux/debugfs.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "smp.h"
#समावेश "hci_debugfs.h"

#घोषणा DEFINE_QUIRK_ATTRIBUTE(__name, __quirk)				      \
अटल sमाप_प्रकार __name ## _पढ़ो(काष्ठा file *file,			      \
				अक्षर __user *user_buf,			      \
				माप_प्रकार count, loff_t *ppos)		      \
अणु									      \
	काष्ठा hci_dev *hdev = file->निजी_data;			      \
	अक्षर buf[3];							      \
									      \
	buf[0] = test_bit(__quirk, &hdev->quirks) ? 'Y' : 'N';		      \
	buf[1] = '\n';							      \
	buf[2] = '\0';							      \
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, 2);	      \
पूर्ण									      \
									      \
अटल sमाप_प्रकार __name ## _ग_लिखो(काष्ठा file *file,			      \
				 स्थिर अक्षर __user *user_buf,		      \
				 माप_प्रकार count, loff_t *ppos)		      \
अणु									      \
	काष्ठा hci_dev *hdev = file->निजी_data;			      \
	bool enable;							      \
	पूर्णांक err;							      \
									      \
	अगर (test_bit(HCI_UP, &hdev->flags))				      \
		वापस -EBUSY;						      \
									      \
	err = kstrtobool_from_user(user_buf, count, &enable);		      \
	अगर (err)							      \
		वापस err;						      \
									      \
	अगर (enable == test_bit(__quirk, &hdev->quirks))			      \
		वापस -EALREADY;					      \
									      \
	change_bit(__quirk, &hdev->quirks);				      \
									      \
	वापस count;							      \
पूर्ण									      \
									      \
अटल स्थिर काष्ठा file_operations __name ## _fops = अणु			      \
	.खोलो		= simple_खोलो,					      \
	.पढ़ो		= __name ## _पढ़ो,				      \
	.ग_लिखो		= __name ## _ग_लिखो,				      \
	.llseek		= शेष_llseek,				      \
पूर्ण									      \

#घोषणा DEFINE_INFO_ATTRIBUTE(__name, __field)				      \
अटल पूर्णांक __name ## _show(काष्ठा seq_file *f, व्योम *ptr)		      \
अणु									      \
	काष्ठा hci_dev *hdev = f->निजी;				      \
									      \
	hci_dev_lock(hdev);						      \
	seq_म_लिखो(f, "%s\n", hdev->__field ? : "");			      \
	hci_dev_unlock(hdev);						      \
									      \
	वापस 0;							      \
पूर्ण									      \
									      \
DEFINE_SHOW_ATTRIBUTE(__name)

अटल पूर्णांक features_show(काष्ठा seq_file *f, व्योम *ptr)
अणु
	काष्ठा hci_dev *hdev = f->निजी;
	u8 p;

	hci_dev_lock(hdev);
	क्रम (p = 0; p < HCI_MAX_PAGES && p <= hdev->max_page; p++)
		seq_म_लिखो(f, "%2u: %8ph\n", p, hdev->features[p]);
	अगर (lmp_le_capable(hdev))
		seq_म_लिखो(f, "LE: %8ph\n", hdev->le_features);
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(features);

अटल पूर्णांक device_id_show(काष्ठा seq_file *f, व्योम *ptr)
अणु
	काष्ठा hci_dev *hdev = f->निजी;

	hci_dev_lock(hdev);
	seq_म_लिखो(f, "%4.4x:%4.4x:%4.4x:%4.4x\n", hdev->devid_source,
		  hdev->devid_venकरोr, hdev->devid_product, hdev->devid_version);
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(device_id);

अटल पूर्णांक device_list_show(काष्ठा seq_file *f, व्योम *ptr)
अणु
	काष्ठा hci_dev *hdev = f->निजी;
	काष्ठा hci_conn_params *p;
	काष्ठा bdaddr_list *b;

	hci_dev_lock(hdev);
	list_क्रम_each_entry(b, &hdev->whitelist, list)
		seq_म_लिखो(f, "%pMR (type %u)\n", &b->bdaddr, b->bdaddr_type);
	list_क्रम_each_entry(p, &hdev->le_conn_params, list) अणु
		seq_म_लिखो(f, "%pMR (type %u) %u\n", &p->addr, p->addr_type,
			   p->स्वतः_connect);
	पूर्ण
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(device_list);

अटल पूर्णांक blacklist_show(काष्ठा seq_file *f, व्योम *p)
अणु
	काष्ठा hci_dev *hdev = f->निजी;
	काष्ठा bdaddr_list *b;

	hci_dev_lock(hdev);
	list_क्रम_each_entry(b, &hdev->blacklist, list)
		seq_म_लिखो(f, "%pMR (type %u)\n", &b->bdaddr, b->bdaddr_type);
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(blacklist);

अटल पूर्णांक blocked_keys_show(काष्ठा seq_file *f, व्योम *p)
अणु
	काष्ठा hci_dev *hdev = f->निजी;
	काष्ठा blocked_key *key;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(key, &hdev->blocked_keys, list)
		seq_म_लिखो(f, "%u %*phN\n", key->type, 16, key->val);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(blocked_keys);

अटल पूर्णांक uuids_show(काष्ठा seq_file *f, व्योम *p)
अणु
	काष्ठा hci_dev *hdev = f->निजी;
	काष्ठा bt_uuid *uuid;

	hci_dev_lock(hdev);
	list_क्रम_each_entry(uuid, &hdev->uuids, list) अणु
		u8 i, val[16];

		/* The Bluetooth UUID values are stored in big endian,
		 * but with reversed byte order. So convert them पूर्णांकo
		 * the right order क्रम the %pUb modअगरier.
		 */
		क्रम (i = 0; i < 16; i++)
			val[i] = uuid->uuid[15 - i];

		seq_म_लिखो(f, "%pUb\n", val);
	पूर्ण
	hci_dev_unlock(hdev);

       वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(uuids);

अटल पूर्णांक remote_oob_show(काष्ठा seq_file *f, व्योम *ptr)
अणु
	काष्ठा hci_dev *hdev = f->निजी;
	काष्ठा oob_data *data;

	hci_dev_lock(hdev);
	list_क्रम_each_entry(data, &hdev->remote_oob_data, list) अणु
		seq_म_लिखो(f, "%pMR (type %u) %u %*phN %*phN %*phN %*phN\n",
			   &data->bdaddr, data->bdaddr_type, data->present,
			   16, data->hash192, 16, data->अक्रम192,
			   16, data->hash256, 16, data->अक्रम256);
	पूर्ण
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(remote_oob);

अटल पूर्णांक conn_info_min_age_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val == 0 || val > hdev->conn_info_max_age)
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->conn_info_min_age = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक conn_info_min_age_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->conn_info_min_age;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(conn_info_min_age_fops, conn_info_min_age_get,
			  conn_info_min_age_set, "%llu\n");

अटल पूर्णांक conn_info_max_age_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val == 0 || val < hdev->conn_info_min_age)
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->conn_info_max_age = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक conn_info_max_age_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->conn_info_max_age;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(conn_info_max_age_fops, conn_info_max_age_get,
			  conn_info_max_age_set, "%llu\n");

अटल sमाप_प्रकार use_debug_keys_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hci_dev *hdev = file->निजी_data;
	अक्षर buf[3];

	buf[0] = hci_dev_test_flag(hdev, HCI_USE_DEBUG_KEYS) ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, 2);
पूर्ण

अटल स्थिर काष्ठा file_operations use_debug_keys_fops = अणु
	.खोलो		= simple_खोलो,
	.पढ़ो		= use_debug_keys_पढ़ो,
	.llseek		= शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार sc_only_mode_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hci_dev *hdev = file->निजी_data;
	अक्षर buf[3];

	buf[0] = hci_dev_test_flag(hdev, HCI_SC_ONLY) ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, 2);
पूर्ण

अटल स्थिर काष्ठा file_operations sc_only_mode_fops = अणु
	.खोलो		= simple_खोलो,
	.पढ़ो		= sc_only_mode_पढ़ो,
	.llseek		= शेष_llseek,
पूर्ण;

DEFINE_INFO_ATTRIBUTE(hardware_info, hw_info);
DEFINE_INFO_ATTRIBUTE(firmware_info, fw_info);

व्योम hci_debugfs_create_common(काष्ठा hci_dev *hdev)
अणु
	debugfs_create_file("features", 0444, hdev->debugfs, hdev,
			    &features_fops);
	debugfs_create_u16("manufacturer", 0444, hdev->debugfs,
			   &hdev->manufacturer);
	debugfs_create_u8("hci_version", 0444, hdev->debugfs, &hdev->hci_ver);
	debugfs_create_u16("hci_revision", 0444, hdev->debugfs, &hdev->hci_rev);
	debugfs_create_u8("hardware_error", 0444, hdev->debugfs,
			  &hdev->hw_error_code);
	debugfs_create_file("device_id", 0444, hdev->debugfs, hdev,
			    &device_id_fops);

	debugfs_create_file("device_list", 0444, hdev->debugfs, hdev,
			    &device_list_fops);
	debugfs_create_file("blacklist", 0444, hdev->debugfs, hdev,
			    &blacklist_fops);
	debugfs_create_file("blocked_keys", 0444, hdev->debugfs, hdev,
			    &blocked_keys_fops);
	debugfs_create_file("uuids", 0444, hdev->debugfs, hdev, &uuids_fops);
	debugfs_create_file("remote_oob", 0400, hdev->debugfs, hdev,
			    &remote_oob_fops);

	debugfs_create_file("conn_info_min_age", 0644, hdev->debugfs, hdev,
			    &conn_info_min_age_fops);
	debugfs_create_file("conn_info_max_age", 0644, hdev->debugfs, hdev,
			    &conn_info_max_age_fops);

	अगर (lmp_ssp_capable(hdev) || lmp_le_capable(hdev))
		debugfs_create_file("use_debug_keys", 0444, hdev->debugfs,
				    hdev, &use_debug_keys_fops);

	अगर (lmp_sc_capable(hdev) || lmp_le_capable(hdev))
		debugfs_create_file("sc_only_mode", 0444, hdev->debugfs,
				    hdev, &sc_only_mode_fops);

	अगर (hdev->hw_info)
		debugfs_create_file("hardware_info", 0444, hdev->debugfs,
				    hdev, &hardware_info_fops);

	अगर (hdev->fw_info)
		debugfs_create_file("firmware_info", 0444, hdev->debugfs,
				    hdev, &firmware_info_fops);
पूर्ण

अटल पूर्णांक inquiry_cache_show(काष्ठा seq_file *f, व्योम *p)
अणु
	काष्ठा hci_dev *hdev = f->निजी;
	काष्ठा discovery_state *cache = &hdev->discovery;
	काष्ठा inquiry_entry *e;

	hci_dev_lock(hdev);

	list_क्रम_each_entry(e, &cache->all, all) अणु
		काष्ठा inquiry_data *data = &e->data;
		seq_म_लिखो(f, "%pMR %d %d %d 0x%.2x%.2x%.2x 0x%.4x %d %d %u\n",
			   &data->bdaddr,
			   data->pscan_rep_mode, data->pscan_period_mode,
			   data->pscan_mode, data->dev_class[2],
			   data->dev_class[1], data->dev_class[0],
			   __le16_to_cpu(data->घड़ी_offset),
			   data->rssi, data->ssp_mode, e->बारtamp);
	पूर्ण

	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(inquiry_cache);

अटल पूर्णांक link_keys_show(काष्ठा seq_file *f, व्योम *ptr)
अणु
	काष्ठा hci_dev *hdev = f->निजी;
	काष्ठा link_key *key;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(key, &hdev->link_keys, list)
		seq_म_लिखो(f, "%pMR %u %*phN %u\n", &key->bdaddr, key->type,
			   HCI_LINK_KEY_SIZE, key->val, key->pin_len);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(link_keys);

अटल पूर्णांक dev_class_show(काष्ठा seq_file *f, व्योम *ptr)
अणु
	काष्ठा hci_dev *hdev = f->निजी;

	hci_dev_lock(hdev);
	seq_म_लिखो(f, "0x%.2x%.2x%.2x\n", hdev->dev_class[2],
		   hdev->dev_class[1], hdev->dev_class[0]);
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(dev_class);

अटल पूर्णांक voice_setting_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->voice_setting;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(voice_setting_fops, voice_setting_get,
			  शून्य, "0x%4.4llx\n");

अटल sमाप_प्रकार ssp_debug_mode_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hci_dev *hdev = file->निजी_data;
	अक्षर buf[3];

	buf[0] = hdev->ssp_debug_mode ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, 2);
पूर्ण

अटल स्थिर काष्ठा file_operations ssp_debug_mode_fops = अणु
	.खोलो		= simple_खोलो,
	.पढ़ो		= ssp_debug_mode_पढ़ो,
	.llseek		= शेष_llseek,
पूर्ण;

अटल पूर्णांक स्वतः_accept_delay_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	hdev->स्वतः_accept_delay = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक min_encrypt_key_size_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val < 1 || val > 16)
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->min_enc_key_size = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक min_encrypt_key_size_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->min_enc_key_size;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(min_encrypt_key_size_fops,
			  min_encrypt_key_size_get,
			  min_encrypt_key_size_set, "%llu\n");

अटल पूर्णांक स्वतः_accept_delay_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->स्वतः_accept_delay;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(स्वतः_accept_delay_fops, स्वतः_accept_delay_get,
			  स्वतः_accept_delay_set, "%llu\n");

अटल sमाप_प्रकार क्रमce_bredr_smp_पढ़ो(काष्ठा file *file,
				    अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hci_dev *hdev = file->निजी_data;
	अक्षर buf[3];

	buf[0] = hci_dev_test_flag(hdev, HCI_FORCE_BREDR_SMP) ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, 2);
पूर्ण

अटल sमाप_प्रकार क्रमce_bredr_smp_ग_लिखो(काष्ठा file *file,
				     स्थिर अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hci_dev *hdev = file->निजी_data;
	bool enable;
	पूर्णांक err;

	err = kstrtobool_from_user(user_buf, count, &enable);
	अगर (err)
		वापस err;

	err = smp_क्रमce_bredr(hdev, enable);
	अगर (err)
		वापस err;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations क्रमce_bredr_smp_fops = अणु
	.खोलो		= simple_खोलो,
	.पढ़ो		= क्रमce_bredr_smp_पढ़ो,
	.ग_लिखो		= क्रमce_bredr_smp_ग_लिखो,
	.llseek		= शेष_llseek,
पूर्ण;

अटल पूर्णांक idle_समयout_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val != 0 && (val < 500 || val > 3600000))
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->idle_समयout = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक idle_समयout_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->idle_समयout;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(idle_समयout_fops, idle_समयout_get,
			  idle_समयout_set, "%llu\n");

अटल पूर्णांक snअगरf_min_पूर्णांकerval_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val == 0 || val % 2 || val > hdev->snअगरf_max_पूर्णांकerval)
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->snअगरf_min_पूर्णांकerval = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक snअगरf_min_पूर्णांकerval_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->snअगरf_min_पूर्णांकerval;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(snअगरf_min_पूर्णांकerval_fops, snअगरf_min_पूर्णांकerval_get,
			  snअगरf_min_पूर्णांकerval_set, "%llu\n");

अटल पूर्णांक snअगरf_max_पूर्णांकerval_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val == 0 || val % 2 || val < hdev->snअगरf_min_पूर्णांकerval)
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->snअगरf_max_पूर्णांकerval = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक snअगरf_max_पूर्णांकerval_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->snअगरf_max_पूर्णांकerval;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(snअगरf_max_पूर्णांकerval_fops, snअगरf_max_पूर्णांकerval_get,
			  snअगरf_max_पूर्णांकerval_set, "%llu\n");

व्योम hci_debugfs_create_bredr(काष्ठा hci_dev *hdev)
अणु
	debugfs_create_file("inquiry_cache", 0444, hdev->debugfs, hdev,
			    &inquiry_cache_fops);
	debugfs_create_file("link_keys", 0400, hdev->debugfs, hdev,
			    &link_keys_fops);
	debugfs_create_file("dev_class", 0444, hdev->debugfs, hdev,
			    &dev_class_fops);
	debugfs_create_file("voice_setting", 0444, hdev->debugfs, hdev,
			    &voice_setting_fops);

	/* If the controller करोes not support BR/EDR Secure Connections
	 * feature, then the BR/EDR SMP channel shall not be present.
	 *
	 * To test this with Bluetooth 4.0 controllers, create a debugfs
	 * चयन that allows क्रमcing BR/EDR SMP support and accepting
	 * cross-transport pairing on non-AES encrypted connections.
	 */
	अगर (!lmp_sc_capable(hdev))
		debugfs_create_file("force_bredr_smp", 0644, hdev->debugfs,
				    hdev, &क्रमce_bredr_smp_fops);

	अगर (lmp_ssp_capable(hdev)) अणु
		debugfs_create_file("ssp_debug_mode", 0444, hdev->debugfs,
				    hdev, &ssp_debug_mode_fops);
		debugfs_create_file("min_encrypt_key_size", 0644, hdev->debugfs,
				    hdev, &min_encrypt_key_size_fops);
		debugfs_create_file("auto_accept_delay", 0644, hdev->debugfs,
				    hdev, &स्वतः_accept_delay_fops);
	पूर्ण

	अगर (lmp_snअगरf_capable(hdev)) अणु
		debugfs_create_file("idle_timeout", 0644, hdev->debugfs,
				    hdev, &idle_समयout_fops);
		debugfs_create_file("sniff_min_interval", 0644, hdev->debugfs,
				    hdev, &snअगरf_min_पूर्णांकerval_fops);
		debugfs_create_file("sniff_max_interval", 0644, hdev->debugfs,
				    hdev, &snअगरf_max_पूर्णांकerval_fops);
	पूर्ण
पूर्ण

अटल पूर्णांक identity_show(काष्ठा seq_file *f, व्योम *p)
अणु
	काष्ठा hci_dev *hdev = f->निजी;
	bdaddr_t addr;
	u8 addr_type;

	hci_dev_lock(hdev);

	hci_copy_identity_address(hdev, &addr, &addr_type);

	seq_म_लिखो(f, "%pMR (type %u) %*phN %pMR\n", &addr, addr_type,
		   16, hdev->irk, &hdev->rpa);

	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(identity);

अटल पूर्णांक rpa_समयout_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	/* Require the RPA समयout to be at least 30 seconds and at most
	 * 24 hours.
	 */
	अगर (val < 30 || val > (60 * 60 * 24))
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->rpa_समयout = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक rpa_समयout_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->rpa_समयout;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(rpa_समयout_fops, rpa_समयout_get,
			  rpa_समयout_set, "%llu\n");

अटल पूर्णांक अक्रमom_address_show(काष्ठा seq_file *f, व्योम *p)
अणु
	काष्ठा hci_dev *hdev = f->निजी;

	hci_dev_lock(hdev);
	seq_म_लिखो(f, "%pMR\n", &hdev->अक्रमom_addr);
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(अक्रमom_address);

अटल पूर्णांक अटल_address_show(काष्ठा seq_file *f, व्योम *p)
अणु
	काष्ठा hci_dev *hdev = f->निजी;

	hci_dev_lock(hdev);
	seq_म_लिखो(f, "%pMR\n", &hdev->अटल_addr);
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(अटल_address);

अटल sमाप_प्रकार क्रमce_अटल_address_पढ़ो(काष्ठा file *file,
					 अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hci_dev *hdev = file->निजी_data;
	अक्षर buf[3];

	buf[0] = hci_dev_test_flag(hdev, HCI_FORCE_STATIC_ADDR) ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, 2);
पूर्ण

अटल sमाप_प्रकार क्रमce_अटल_address_ग_लिखो(काष्ठा file *file,
					  स्थिर अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hci_dev *hdev = file->निजी_data;
	bool enable;
	पूर्णांक err;

	अगर (test_bit(HCI_UP, &hdev->flags))
		वापस -EBUSY;

	err = kstrtobool_from_user(user_buf, count, &enable);
	अगर (err)
		वापस err;

	अगर (enable == hci_dev_test_flag(hdev, HCI_FORCE_STATIC_ADDR))
		वापस -EALREADY;

	hci_dev_change_flag(hdev, HCI_FORCE_STATIC_ADDR);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations क्रमce_अटल_address_fops = अणु
	.खोलो		= simple_खोलो,
	.पढ़ो		= क्रमce_अटल_address_पढ़ो,
	.ग_लिखो		= क्रमce_अटल_address_ग_लिखो,
	.llseek		= शेष_llseek,
पूर्ण;

अटल पूर्णांक white_list_show(काष्ठा seq_file *f, व्योम *ptr)
अणु
	काष्ठा hci_dev *hdev = f->निजी;
	काष्ठा bdaddr_list *b;

	hci_dev_lock(hdev);
	list_क्रम_each_entry(b, &hdev->le_white_list, list)
		seq_म_लिखो(f, "%pMR (type %u)\n", &b->bdaddr, b->bdaddr_type);
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(white_list);

अटल पूर्णांक resolv_list_show(काष्ठा seq_file *f, व्योम *ptr)
अणु
	काष्ठा hci_dev *hdev = f->निजी;
	काष्ठा bdaddr_list *b;

	hci_dev_lock(hdev);
	list_क्रम_each_entry(b, &hdev->le_resolv_list, list)
		seq_म_लिखो(f, "%pMR (type %u)\n", &b->bdaddr, b->bdaddr_type);
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(resolv_list);

अटल पूर्णांक identity_resolving_keys_show(काष्ठा seq_file *f, व्योम *ptr)
अणु
	काष्ठा hci_dev *hdev = f->निजी;
	काष्ठा smp_irk *irk;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(irk, &hdev->identity_resolving_keys, list) अणु
		seq_म_लिखो(f, "%pMR (type %u) %*phN %pMR\n",
			   &irk->bdaddr, irk->addr_type,
			   16, irk->val, &irk->rpa);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(identity_resolving_keys);

अटल पूर्णांक दीर्घ_term_keys_show(काष्ठा seq_file *f, व्योम *ptr)
अणु
	काष्ठा hci_dev *hdev = f->निजी;
	काष्ठा smp_ltk *ltk;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ltk, &hdev->दीर्घ_term_keys, list)
		seq_म_लिखो(f, "%pMR (type %u) %u 0x%02x %u %.4x %.16llx %*phN\n",
			   &ltk->bdaddr, ltk->bdaddr_type, ltk->authenticated,
			   ltk->type, ltk->enc_size, __le16_to_cpu(ltk->eभाग),
			   __le64_to_cpu(ltk->अक्रम), 16, ltk->val);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(दीर्घ_term_keys);

अटल पूर्णांक conn_min_पूर्णांकerval_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val < 0x0006 || val > 0x0c80 || val > hdev->le_conn_max_पूर्णांकerval)
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->le_conn_min_पूर्णांकerval = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक conn_min_पूर्णांकerval_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->le_conn_min_पूर्णांकerval;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(conn_min_पूर्णांकerval_fops, conn_min_पूर्णांकerval_get,
			  conn_min_पूर्णांकerval_set, "%llu\n");

अटल पूर्णांक conn_max_पूर्णांकerval_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val < 0x0006 || val > 0x0c80 || val < hdev->le_conn_min_पूर्णांकerval)
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->le_conn_max_पूर्णांकerval = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक conn_max_पूर्णांकerval_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->le_conn_max_पूर्णांकerval;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(conn_max_पूर्णांकerval_fops, conn_max_पूर्णांकerval_get,
			  conn_max_पूर्णांकerval_set, "%llu\n");

अटल पूर्णांक conn_latency_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val > 0x01f3)
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->le_conn_latency = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक conn_latency_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->le_conn_latency;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(conn_latency_fops, conn_latency_get,
			  conn_latency_set, "%llu\n");

अटल पूर्णांक supervision_समयout_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val < 0x000a || val > 0x0c80)
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->le_supv_समयout = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक supervision_समयout_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->le_supv_समयout;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(supervision_समयout_fops, supervision_समयout_get,
			  supervision_समयout_set, "%llu\n");

अटल पूर्णांक adv_channel_map_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val < 0x01 || val > 0x07)
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->le_adv_channel_map = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक adv_channel_map_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->le_adv_channel_map;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(adv_channel_map_fops, adv_channel_map_get,
			  adv_channel_map_set, "%llu\n");

अटल पूर्णांक adv_min_पूर्णांकerval_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val < 0x0020 || val > 0x4000 || val > hdev->le_adv_max_पूर्णांकerval)
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->le_adv_min_पूर्णांकerval = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक adv_min_पूर्णांकerval_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->le_adv_min_पूर्णांकerval;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(adv_min_पूर्णांकerval_fops, adv_min_पूर्णांकerval_get,
			  adv_min_पूर्णांकerval_set, "%llu\n");

अटल पूर्णांक adv_max_पूर्णांकerval_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val < 0x0020 || val > 0x4000 || val < hdev->le_adv_min_पूर्णांकerval)
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->le_adv_max_पूर्णांकerval = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक adv_max_पूर्णांकerval_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->le_adv_max_पूर्णांकerval;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(adv_max_पूर्णांकerval_fops, adv_max_पूर्णांकerval_get,
			  adv_max_पूर्णांकerval_set, "%llu\n");

अटल पूर्णांक min_key_size_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val > hdev->le_max_key_size || val < SMP_MIN_ENC_KEY_SIZE)
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->le_min_key_size = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक min_key_size_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->le_min_key_size;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(min_key_size_fops, min_key_size_get,
			  min_key_size_set, "%llu\n");

अटल पूर्णांक max_key_size_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val > SMP_MAX_ENC_KEY_SIZE || val < hdev->le_min_key_size)
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->le_max_key_size = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक max_key_size_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->le_max_key_size;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(max_key_size_fops, max_key_size_get,
			  max_key_size_set, "%llu\n");

अटल पूर्णांक auth_payload_समयout_set(व्योम *data, u64 val)
अणु
	काष्ठा hci_dev *hdev = data;

	अगर (val < 0x0001 || val > 0xffff)
		वापस -EINVAL;

	hci_dev_lock(hdev);
	hdev->auth_payload_समयout = val;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक auth_payload_समयout_get(व्योम *data, u64 *val)
अणु
	काष्ठा hci_dev *hdev = data;

	hci_dev_lock(hdev);
	*val = hdev->auth_payload_समयout;
	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(auth_payload_समयout_fops,
			  auth_payload_समयout_get,
			  auth_payload_समयout_set, "%llu\n");

अटल sमाप_प्रकार क्रमce_no_miपंचांग_पढ़ो(काष्ठा file *file,
				  अक्षर __user *user_buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hci_dev *hdev = file->निजी_data;
	अक्षर buf[3];

	buf[0] = hci_dev_test_flag(hdev, HCI_FORCE_NO_MITM) ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = '\0';
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, 2);
पूर्ण

अटल sमाप_प्रकार क्रमce_no_miपंचांग_ग_लिखो(काष्ठा file *file,
				   स्थिर अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hci_dev *hdev = file->निजी_data;
	अक्षर buf[32];
	माप_प्रकार buf_size = min(count, (माप(buf) - 1));
	bool enable;

	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;

	buf[buf_size] = '\0';
	अगर (strtobool(buf, &enable))
		वापस -EINVAL;

	अगर (enable == hci_dev_test_flag(hdev, HCI_FORCE_NO_MITM))
		वापस -EALREADY;

	hci_dev_change_flag(hdev, HCI_FORCE_NO_MITM);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations क्रमce_no_miपंचांग_fops = अणु
	.खोलो		= simple_खोलो,
	.पढ़ो		= क्रमce_no_miपंचांग_पढ़ो,
	.ग_लिखो		= क्रमce_no_miपंचांग_ग_लिखो,
	.llseek		= शेष_llseek,
पूर्ण;

DEFINE_QUIRK_ATTRIBUTE(quirk_strict_duplicate_filter,
		       HCI_QUIRK_STRICT_DUPLICATE_FILTER);
DEFINE_QUIRK_ATTRIBUTE(quirk_simultaneous_discovery,
		       HCI_QUIRK_SIMULTANEOUS_DISCOVERY);

व्योम hci_debugfs_create_le(काष्ठा hci_dev *hdev)
अणु
	debugfs_create_file("identity", 0400, hdev->debugfs, hdev,
			    &identity_fops);
	debugfs_create_file("rpa_timeout", 0644, hdev->debugfs, hdev,
			    &rpa_समयout_fops);
	debugfs_create_file("random_address", 0444, hdev->debugfs, hdev,
			    &अक्रमom_address_fops);
	debugfs_create_file("static_address", 0444, hdev->debugfs, hdev,
			    &अटल_address_fops);

	/* For controllers with a खुला address, provide a debug
	 * option to क्रमce the usage of the configured अटल
	 * address. By शेष the खुला address is used.
	 */
	अगर (bacmp(&hdev->bdaddr, BDADDR_ANY))
		debugfs_create_file("force_static_address", 0644,
				    hdev->debugfs, hdev,
				    &क्रमce_अटल_address_fops);

	debugfs_create_u8("white_list_size", 0444, hdev->debugfs,
			  &hdev->le_white_list_size);
	debugfs_create_file("white_list", 0444, hdev->debugfs, hdev,
			    &white_list_fops);
	debugfs_create_u8("resolv_list_size", 0444, hdev->debugfs,
			  &hdev->le_resolv_list_size);
	debugfs_create_file("resolv_list", 0444, hdev->debugfs, hdev,
			    &resolv_list_fops);
	debugfs_create_file("identity_resolving_keys", 0400, hdev->debugfs,
			    hdev, &identity_resolving_keys_fops);
	debugfs_create_file("long_term_keys", 0400, hdev->debugfs, hdev,
			    &दीर्घ_term_keys_fops);
	debugfs_create_file("conn_min_interval", 0644, hdev->debugfs, hdev,
			    &conn_min_पूर्णांकerval_fops);
	debugfs_create_file("conn_max_interval", 0644, hdev->debugfs, hdev,
			    &conn_max_पूर्णांकerval_fops);
	debugfs_create_file("conn_latency", 0644, hdev->debugfs, hdev,
			    &conn_latency_fops);
	debugfs_create_file("supervision_timeout", 0644, hdev->debugfs, hdev,
			    &supervision_समयout_fops);
	debugfs_create_file("adv_channel_map", 0644, hdev->debugfs, hdev,
			    &adv_channel_map_fops);
	debugfs_create_file("adv_min_interval", 0644, hdev->debugfs, hdev,
			    &adv_min_पूर्णांकerval_fops);
	debugfs_create_file("adv_max_interval", 0644, hdev->debugfs, hdev,
			    &adv_max_पूर्णांकerval_fops);
	debugfs_create_u16("discov_interleaved_timeout", 0644, hdev->debugfs,
			   &hdev->discov_पूर्णांकerleaved_समयout);
	debugfs_create_file("min_key_size", 0644, hdev->debugfs, hdev,
			    &min_key_size_fops);
	debugfs_create_file("max_key_size", 0644, hdev->debugfs, hdev,
			    &max_key_size_fops);
	debugfs_create_file("auth_payload_timeout", 0644, hdev->debugfs, hdev,
			    &auth_payload_समयout_fops);
	debugfs_create_file("force_no_mitm", 0644, hdev->debugfs, hdev,
			    &क्रमce_no_miपंचांग_fops);

	debugfs_create_file("quirk_strict_duplicate_filter", 0644,
			    hdev->debugfs, hdev,
			    &quirk_strict_duplicate_filter_fops);
	debugfs_create_file("quirk_simultaneous_discovery", 0644,
			    hdev->debugfs, hdev,
			    &quirk_simultaneous_discovery_fops);
पूर्ण

व्योम hci_debugfs_create_conn(काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;
	अक्षर name[6];

	अगर (IS_ERR_OR_शून्य(hdev->debugfs))
		वापस;

	snम_लिखो(name, माप(name), "%u", conn->handle);
	conn->debugfs = debugfs_create_dir(name, hdev->debugfs);
पूर्ण
