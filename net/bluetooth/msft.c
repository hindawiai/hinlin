<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Google Corporation
 */

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/mgmt.h>

#समावेश "hci_request.h"
#समावेश "mgmt_util.h"
#समावेश "msft.h"

#घोषणा MSFT_RSSI_THRESHOLD_VALUE_MIN		-127
#घोषणा MSFT_RSSI_THRESHOLD_VALUE_MAX		20
#घोषणा MSFT_RSSI_LOW_TIMEOUT_MAX		0x3C

#घोषणा MSFT_OP_READ_SUPPORTED_FEATURES		0x00
काष्ठा msft_cp_पढ़ो_supported_features अणु
	__u8   sub_opcode;
पूर्ण __packed;

काष्ठा msft_rp_पढ़ो_supported_features अणु
	__u8   status;
	__u8   sub_opcode;
	__le64 features;
	__u8   evt_prefix_len;
	__u8   evt_prefix[];
पूर्ण __packed;

#घोषणा MSFT_OP_LE_MONITOR_ADVERTISEMENT	0x03
#घोषणा MSFT_MONITOR_ADVERTISEMENT_TYPE_PATTERN	0x01
काष्ठा msft_le_monitor_advertisement_pattern अणु
	__u8 length;
	__u8 data_type;
	__u8 start_byte;
	__u8 pattern[0];
पूर्ण;

काष्ठा msft_le_monitor_advertisement_pattern_data अणु
	__u8 count;
	__u8 data[0];
पूर्ण;

काष्ठा msft_cp_le_monitor_advertisement अणु
	__u8 sub_opcode;
	__s8 rssi_high;
	__s8 rssi_low;
	__u8 rssi_low_पूर्णांकerval;
	__u8 rssi_sampling_period;
	__u8 cond_type;
	__u8 data[0];
पूर्ण __packed;

काष्ठा msft_rp_le_monitor_advertisement अणु
	__u8 status;
	__u8 sub_opcode;
	__u8 handle;
पूर्ण __packed;

#घोषणा MSFT_OP_LE_CANCEL_MONITOR_ADVERTISEMENT	0x04
काष्ठा msft_cp_le_cancel_monitor_advertisement अणु
	__u8 sub_opcode;
	__u8 handle;
पूर्ण __packed;

काष्ठा msft_rp_le_cancel_monitor_advertisement अणु
	__u8 status;
	__u8 sub_opcode;
पूर्ण __packed;

#घोषणा MSFT_OP_LE_SET_ADVERTISEMENT_FILTER_ENABLE	0x05
काष्ठा msft_cp_le_set_advertisement_filter_enable अणु
	__u8 sub_opcode;
	__u8 enable;
पूर्ण __packed;

काष्ठा msft_rp_le_set_advertisement_filter_enable अणु
	__u8 status;
	__u8 sub_opcode;
पूर्ण __packed;

काष्ठा msft_monitor_advertisement_handle_data अणु
	__u8  msft_handle;
	__u16 mgmt_handle;
	काष्ठा list_head list;
पूर्ण;

काष्ठा msft_data अणु
	__u64 features;
	__u8  evt_prefix_len;
	__u8  *evt_prefix;
	काष्ठा list_head handle_map;
	__u16 pending_add_handle;
	__u16 pending_हटाओ_handle;
	__u8 reरेजिस्टरing;
	__u8 filter_enabled;
पूर्ण;

अटल पूर्णांक __msft_add_monitor_pattern(काष्ठा hci_dev *hdev,
				      काष्ठा adv_monitor *monitor);

bool msft_monitor_supported(काष्ठा hci_dev *hdev)
अणु
	वापस !!(msft_get_features(hdev) & MSFT_FEATURE_MASK_LE_ADV_MONITOR);
पूर्ण

अटल bool पढ़ो_supported_features(काष्ठा hci_dev *hdev,
				    काष्ठा msft_data *msft)
अणु
	काष्ठा msft_cp_पढ़ो_supported_features cp;
	काष्ठा msft_rp_पढ़ो_supported_features *rp;
	काष्ठा sk_buff *skb;

	cp.sub_opcode = MSFT_OP_READ_SUPPORTED_FEATURES;

	skb = __hci_cmd_sync(hdev, hdev->msft_opcode, माप(cp), &cp,
			     HCI_CMD_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "Failed to read MSFT supported features (%ld)",
			   PTR_ERR(skb));
		वापस false;
	पूर्ण

	अगर (skb->len < माप(*rp)) अणु
		bt_dev_err(hdev, "MSFT supported features length mismatch");
		जाओ failed;
	पूर्ण

	rp = (काष्ठा msft_rp_पढ़ो_supported_features *)skb->data;

	अगर (rp->sub_opcode != MSFT_OP_READ_SUPPORTED_FEATURES)
		जाओ failed;

	अगर (rp->evt_prefix_len > 0) अणु
		msft->evt_prefix = kmemdup(rp->evt_prefix, rp->evt_prefix_len,
					   GFP_KERNEL);
		अगर (!msft->evt_prefix)
			जाओ failed;
	पूर्ण

	msft->evt_prefix_len = rp->evt_prefix_len;
	msft->features = __le64_to_cpu(rp->features);

	अगर (msft->features & MSFT_FEATURE_MASK_CURVE_VALIDITY)
		hdev->msft_curve_validity = true;

	kमुक्त_skb(skb);
	वापस true;

failed:
	kमुक्त_skb(skb);
	वापस false;
पूर्ण

/* This function requires the caller holds hdev->lock */
अटल व्योम reरेजिस्टर_monitor_on_restart(काष्ठा hci_dev *hdev, पूर्णांक handle)
अणु
	काष्ठा adv_monitor *monitor;
	काष्ठा msft_data *msft = hdev->msft_data;
	पूर्णांक err;

	जबतक (1) अणु
		monitor = idr_get_next(&hdev->adv_monitors_idr, &handle);
		अगर (!monitor) अणु
			/* All monitors have been reरेजिस्टरed */
			msft->reरेजिस्टरing = false;
			hci_update_background_scan(hdev);
			वापस;
		पूर्ण

		msft->pending_add_handle = (u16)handle;
		err = __msft_add_monitor_pattern(hdev, monitor);

		/* If success, we वापस and रुको क्रम monitor added callback */
		अगर (!err)
			वापस;

		/* Otherwise हटाओ the monitor and keep रेजिस्टरing */
		hci_मुक्त_adv_monitor(hdev, monitor);
		handle++;
	पूर्ण
पूर्ण

व्योम msft_करो_खोलो(काष्ठा hci_dev *hdev)
अणु
	काष्ठा msft_data *msft;

	अगर (hdev->msft_opcode == HCI_OP_NOP)
		वापस;

	bt_dev_dbg(hdev, "Initialize MSFT extension");

	msft = kzalloc(माप(*msft), GFP_KERNEL);
	अगर (!msft)
		वापस;

	अगर (!पढ़ो_supported_features(hdev, msft)) अणु
		kमुक्त(msft);
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&msft->handle_map);
	hdev->msft_data = msft;

	अगर (msft_monitor_supported(hdev)) अणु
		msft->reरेजिस्टरing = true;
		msft_set_filter_enable(hdev, true);
		reरेजिस्टर_monitor_on_restart(hdev, 0);
	पूर्ण
पूर्ण

व्योम msft_करो_बंद(काष्ठा hci_dev *hdev)
अणु
	काष्ठा msft_data *msft = hdev->msft_data;
	काष्ठा msft_monitor_advertisement_handle_data *handle_data, *पंचांगp;
	काष्ठा adv_monitor *monitor;

	अगर (!msft)
		वापस;

	bt_dev_dbg(hdev, "Cleanup of MSFT extension");

	hdev->msft_data = शून्य;

	list_क्रम_each_entry_safe(handle_data, पंचांगp, &msft->handle_map, list) अणु
		monitor = idr_find(&hdev->adv_monitors_idr,
				   handle_data->mgmt_handle);

		अगर (monitor && monitor->state == ADV_MONITOR_STATE_OFFLOADED)
			monitor->state = ADV_MONITOR_STATE_REGISTERED;

		list_del(&handle_data->list);
		kमुक्त(handle_data);
	पूर्ण

	kमुक्त(msft->evt_prefix);
	kमुक्त(msft);
पूर्ण

व्योम msft_venकरोr_evt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा msft_data *msft = hdev->msft_data;
	u8 event;

	अगर (!msft)
		वापस;

	/* When the extension has defined an event prefix, check that it
	 * matches, and otherwise just वापस.
	 */
	अगर (msft->evt_prefix_len > 0) अणु
		अगर (skb->len < msft->evt_prefix_len)
			वापस;

		अगर (स_भेद(skb->data, msft->evt_prefix, msft->evt_prefix_len))
			वापस;

		skb_pull(skb, msft->evt_prefix_len);
	पूर्ण

	/* Every event starts at least with an event code and the rest of
	 * the data is variable and depends on the event code.
	 */
	अगर (skb->len < 1)
		वापस;

	event = *skb->data;
	skb_pull(skb, 1);

	bt_dev_dbg(hdev, "MSFT vendor event %u", event);
पूर्ण

__u64 msft_get_features(काष्ठा hci_dev *hdev)
अणु
	काष्ठा msft_data *msft = hdev->msft_data;

	वापस msft ? msft->features : 0;
पूर्ण

/* is_mgmt = true matches the handle exposed to userspace via mgmt.
 * is_mgmt = false matches the handle used by the msft controller.
 * This function requires the caller holds hdev->lock
 */
अटल काष्ठा msft_monitor_advertisement_handle_data *msft_find_handle_data
				(काष्ठा hci_dev *hdev, u16 handle, bool is_mgmt)
अणु
	काष्ठा msft_monitor_advertisement_handle_data *entry;
	काष्ठा msft_data *msft = hdev->msft_data;

	list_क्रम_each_entry(entry, &msft->handle_map, list) अणु
		अगर (is_mgmt && entry->mgmt_handle == handle)
			वापस entry;
		अगर (!is_mgmt && entry->msft_handle == handle)
			वापस entry;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम msft_le_monitor_advertisement_cb(काष्ठा hci_dev *hdev,
					     u8 status, u16 opcode,
					     काष्ठा sk_buff *skb)
अणु
	काष्ठा msft_rp_le_monitor_advertisement *rp;
	काष्ठा adv_monitor *monitor;
	काष्ठा msft_monitor_advertisement_handle_data *handle_data;
	काष्ठा msft_data *msft = hdev->msft_data;

	hci_dev_lock(hdev);

	monitor = idr_find(&hdev->adv_monitors_idr, msft->pending_add_handle);
	अगर (!monitor) अणु
		bt_dev_err(hdev, "msft add advmon: monitor %d is not found!",
			   msft->pending_add_handle);
		status = HCI_ERROR_UNSPECIFIED;
		जाओ unlock;
	पूर्ण

	अगर (status)
		जाओ unlock;

	rp = (काष्ठा msft_rp_le_monitor_advertisement *)skb->data;
	अगर (skb->len < माप(*rp)) अणु
		status = HCI_ERROR_UNSPECIFIED;
		जाओ unlock;
	पूर्ण

	handle_data = kदो_स्मृति(माप(*handle_data), GFP_KERNEL);
	अगर (!handle_data) अणु
		status = HCI_ERROR_UNSPECIFIED;
		जाओ unlock;
	पूर्ण

	handle_data->mgmt_handle = monitor->handle;
	handle_data->msft_handle = rp->handle;
	INIT_LIST_HEAD(&handle_data->list);
	list_add(&handle_data->list, &msft->handle_map);

	monitor->state = ADV_MONITOR_STATE_OFFLOADED;

unlock:
	अगर (status && monitor)
		hci_मुक्त_adv_monitor(hdev, monitor);

	/* If in restart/reरेजिस्टर sequence, keep रेजिस्टरing. */
	अगर (msft->reरेजिस्टरing)
		reरेजिस्टर_monitor_on_restart(hdev,
					      msft->pending_add_handle + 1);

	hci_dev_unlock(hdev);

	अगर (!msft->reरेजिस्टरing)
		hci_add_adv_patterns_monitor_complete(hdev, status);
पूर्ण

अटल व्योम msft_le_cancel_monitor_advertisement_cb(काष्ठा hci_dev *hdev,
						    u8 status, u16 opcode,
						    काष्ठा sk_buff *skb)
अणु
	काष्ठा msft_cp_le_cancel_monitor_advertisement *cp;
	काष्ठा msft_rp_le_cancel_monitor_advertisement *rp;
	काष्ठा adv_monitor *monitor;
	काष्ठा msft_monitor_advertisement_handle_data *handle_data;
	काष्ठा msft_data *msft = hdev->msft_data;
	पूर्णांक err;
	bool pending;

	अगर (status)
		जाओ करोne;

	rp = (काष्ठा msft_rp_le_cancel_monitor_advertisement *)skb->data;
	अगर (skb->len < माप(*rp)) अणु
		status = HCI_ERROR_UNSPECIFIED;
		जाओ करोne;
	पूर्ण

	hci_dev_lock(hdev);

	cp = hci_sent_cmd_data(hdev, hdev->msft_opcode);
	handle_data = msft_find_handle_data(hdev, cp->handle, false);

	अगर (handle_data) अणु
		monitor = idr_find(&hdev->adv_monitors_idr,
				   handle_data->mgmt_handle);
		अगर (monitor)
			hci_मुक्त_adv_monitor(hdev, monitor);

		list_del(&handle_data->list);
		kमुक्त(handle_data);
	पूर्ण

	/* If हटाओ all monitors is required, we need to जारी the process
	 * here because the earlier it was छोड़ोd when रुकोing क्रम the
	 * response from controller.
	 */
	अगर (msft->pending_हटाओ_handle == 0) अणु
		pending = hci_हटाओ_all_adv_monitor(hdev, &err);
		अगर (pending) अणु
			hci_dev_unlock(hdev);
			वापस;
		पूर्ण

		अगर (err)
			status = HCI_ERROR_UNSPECIFIED;
	पूर्ण

	hci_dev_unlock(hdev);

करोne:
	hci_हटाओ_adv_monitor_complete(hdev, status);
पूर्ण

अटल व्योम msft_le_set_advertisement_filter_enable_cb(काष्ठा hci_dev *hdev,
						       u8 status, u16 opcode,
						       काष्ठा sk_buff *skb)
अणु
	काष्ठा msft_cp_le_set_advertisement_filter_enable *cp;
	काष्ठा msft_rp_le_set_advertisement_filter_enable *rp;
	काष्ठा msft_data *msft = hdev->msft_data;

	rp = (काष्ठा msft_rp_le_set_advertisement_filter_enable *)skb->data;
	अगर (skb->len < माप(*rp))
		वापस;

	/* Error 0x0C would be वापसed अगर the filter enabled status is
	 * alपढ़ोy set to whatever we were trying to set.
	 * Although the शेष state should be disabled, some controller set
	 * the initial value to enabled. Because there is no way to know the
	 * actual initial value beक्रमe sending this command, here we also treat
	 * error 0x0C as success.
	 */
	अगर (status != 0x00 && status != 0x0C)
		वापस;

	hci_dev_lock(hdev);

	cp = hci_sent_cmd_data(hdev, hdev->msft_opcode);
	msft->filter_enabled = cp->enable;

	अगर (status == 0x0C)
		bt_dev_warn(hdev, "MSFT filter_enable is already %s",
			    cp->enable ? "on" : "off");

	hci_dev_unlock(hdev);
पूर्ण

अटल bool msft_monitor_rssi_valid(काष्ठा adv_monitor *monitor)
अणु
	काष्ठा adv_rssi_thresholds *r = &monitor->rssi;

	अगर (r->high_threshold < MSFT_RSSI_THRESHOLD_VALUE_MIN ||
	    r->high_threshold > MSFT_RSSI_THRESHOLD_VALUE_MAX ||
	    r->low_threshold < MSFT_RSSI_THRESHOLD_VALUE_MIN ||
	    r->low_threshold > MSFT_RSSI_THRESHOLD_VALUE_MAX)
		वापस false;

	/* High_threshold_समयout is not supported,
	 * once high_threshold is reached, events are immediately reported.
	 */
	अगर (r->high_threshold_समयout != 0)
		वापस false;

	अगर (r->low_threshold_समयout > MSFT_RSSI_LOW_TIMEOUT_MAX)
		वापस false;

	/* Sampling period from 0x00 to 0xFF are all allowed */
	वापस true;
पूर्ण

अटल bool msft_monitor_pattern_valid(काष्ठा adv_monitor *monitor)
अणु
	वापस msft_monitor_rssi_valid(monitor);
	/* No additional check needed क्रम pattern-based monitor */
पूर्ण

/* This function requires the caller holds hdev->lock */
अटल पूर्णांक __msft_add_monitor_pattern(काष्ठा hci_dev *hdev,
				      काष्ठा adv_monitor *monitor)
अणु
	काष्ठा msft_cp_le_monitor_advertisement *cp;
	काष्ठा msft_le_monitor_advertisement_pattern_data *pattern_data;
	काष्ठा msft_le_monitor_advertisement_pattern *pattern;
	काष्ठा adv_pattern *entry;
	काष्ठा hci_request req;
	काष्ठा msft_data *msft = hdev->msft_data;
	माप_प्रकार total_size = माप(*cp) + माप(*pattern_data);
	सूचक_भेद_प्रकार offset = 0;
	u8 pattern_count = 0;
	पूर्णांक err = 0;

	अगर (!msft_monitor_pattern_valid(monitor))
		वापस -EINVAL;

	list_क्रम_each_entry(entry, &monitor->patterns, list) अणु
		pattern_count++;
		total_size += माप(*pattern) + entry->length;
	पूर्ण

	cp = kदो_स्मृति(total_size, GFP_KERNEL);
	अगर (!cp)
		वापस -ENOMEM;

	cp->sub_opcode = MSFT_OP_LE_MONITOR_ADVERTISEMENT;
	cp->rssi_high = monitor->rssi.high_threshold;
	cp->rssi_low = monitor->rssi.low_threshold;
	cp->rssi_low_पूर्णांकerval = (u8)monitor->rssi.low_threshold_समयout;
	cp->rssi_sampling_period = monitor->rssi.sampling_period;

	cp->cond_type = MSFT_MONITOR_ADVERTISEMENT_TYPE_PATTERN;

	pattern_data = (व्योम *)cp->data;
	pattern_data->count = pattern_count;

	list_क्रम_each_entry(entry, &monitor->patterns, list) अणु
		pattern = (व्योम *)(pattern_data->data + offset);
		/* the length also includes data_type and offset */
		pattern->length = entry->length + 2;
		pattern->data_type = entry->ad_type;
		pattern->start_byte = entry->offset;
		स_नकल(pattern->pattern, entry->value, entry->length);
		offset += माप(*pattern) + entry->length;
	पूर्ण

	hci_req_init(&req, hdev);
	hci_req_add(&req, hdev->msft_opcode, total_size, cp);
	err = hci_req_run_skb(&req, msft_le_monitor_advertisement_cb);
	kमुक्त(cp);

	अगर (!err)
		msft->pending_add_handle = monitor->handle;

	वापस err;
पूर्ण

/* This function requires the caller holds hdev->lock */
पूर्णांक msft_add_monitor_pattern(काष्ठा hci_dev *hdev, काष्ठा adv_monitor *monitor)
अणु
	काष्ठा msft_data *msft = hdev->msft_data;

	अगर (!msft)
		वापस -EOPNOTSUPP;

	अगर (msft->reरेजिस्टरing)
		वापस -EBUSY;

	वापस __msft_add_monitor_pattern(hdev, monitor);
पूर्ण

/* This function requires the caller holds hdev->lock */
पूर्णांक msft_हटाओ_monitor(काष्ठा hci_dev *hdev, काष्ठा adv_monitor *monitor,
			u16 handle)
अणु
	काष्ठा msft_cp_le_cancel_monitor_advertisement cp;
	काष्ठा msft_monitor_advertisement_handle_data *handle_data;
	काष्ठा hci_request req;
	काष्ठा msft_data *msft = hdev->msft_data;
	पूर्णांक err = 0;

	अगर (!msft)
		वापस -EOPNOTSUPP;

	अगर (msft->reरेजिस्टरing)
		वापस -EBUSY;

	handle_data = msft_find_handle_data(hdev, monitor->handle, true);

	/* If no matched handle, just हटाओ without telling controller */
	अगर (!handle_data)
		वापस -ENOENT;

	cp.sub_opcode = MSFT_OP_LE_CANCEL_MONITOR_ADVERTISEMENT;
	cp.handle = handle_data->msft_handle;

	hci_req_init(&req, hdev);
	hci_req_add(&req, hdev->msft_opcode, माप(cp), &cp);
	err = hci_req_run_skb(&req, msft_le_cancel_monitor_advertisement_cb);

	अगर (!err)
		msft->pending_हटाओ_handle = handle;

	वापस err;
पूर्ण

व्योम msft_req_add_set_filter_enable(काष्ठा hci_request *req, bool enable)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा msft_cp_le_set_advertisement_filter_enable cp;

	cp.sub_opcode = MSFT_OP_LE_SET_ADVERTISEMENT_FILTER_ENABLE;
	cp.enable = enable;

	hci_req_add(req, hdev->msft_opcode, माप(cp), &cp);
पूर्ण

पूर्णांक msft_set_filter_enable(काष्ठा hci_dev *hdev, bool enable)
अणु
	काष्ठा hci_request req;
	काष्ठा msft_data *msft = hdev->msft_data;
	पूर्णांक err;

	अगर (!msft)
		वापस -EOPNOTSUPP;

	hci_req_init(&req, hdev);
	msft_req_add_set_filter_enable(&req, enable);
	err = hci_req_run_skb(&req, msft_le_set_advertisement_filter_enable_cb);

	वापस err;
पूर्ण

bool msft_curve_validity(काष्ठा hci_dev *hdev)
अणु
	वापस hdev->msft_curve_validity;
पूर्ण
