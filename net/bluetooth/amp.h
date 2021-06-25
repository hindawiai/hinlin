<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
   Copyright (c) 2011,2012 Intel Corp.

*/

#अगर_अघोषित __AMP_H
#घोषणा __AMP_H

काष्ठा amp_ctrl अणु
	काष्ठा list_head	list;
	काष्ठा kref		kref;
	__u8			id;
	__u16			assoc_len_so_far;
	__u16			assoc_rem_len;
	__u16			assoc_len;
	__u8			*assoc;
पूर्ण;

पूर्णांक amp_ctrl_put(काष्ठा amp_ctrl *ctrl);
व्योम amp_ctrl_get(काष्ठा amp_ctrl *ctrl);
काष्ठा amp_ctrl *amp_ctrl_add(काष्ठा amp_mgr *mgr, u8 id);
काष्ठा amp_ctrl *amp_ctrl_lookup(काष्ठा amp_mgr *mgr, u8 id);
व्योम amp_ctrl_list_flush(काष्ठा amp_mgr *mgr);

काष्ठा hci_conn *phylink_add(काष्ठा hci_dev *hdev, काष्ठा amp_mgr *mgr,
			     u8 remote_id, bool out);

पूर्णांक phylink_gen_key(काष्ठा hci_conn *hcon, u8 *data, u8 *len, u8 *type);

व्योम amp_पढ़ो_loc_info(काष्ठा hci_dev *hdev, काष्ठा amp_mgr *mgr);
व्योम amp_पढ़ो_loc_assoc_frag(काष्ठा hci_dev *hdev, u8 phy_handle);
व्योम amp_पढ़ो_loc_assoc(काष्ठा hci_dev *hdev, काष्ठा amp_mgr *mgr);
व्योम amp_पढ़ो_loc_assoc_final_data(काष्ठा hci_dev *hdev,
				   काष्ठा hci_conn *hcon);
व्योम amp_create_phylink(काष्ठा hci_dev *hdev, काष्ठा amp_mgr *mgr,
			काष्ठा hci_conn *hcon);
व्योम amp_accept_phylink(काष्ठा hci_dev *hdev, काष्ठा amp_mgr *mgr,
			काष्ठा hci_conn *hcon);

#अगर IS_ENABLED(CONFIG_BT_HS)
व्योम amp_create_logical_link(काष्ठा l2cap_chan *chan);
व्योम amp_disconnect_logical_link(काष्ठा hci_chan *hchan);
#अन्यथा
अटल अंतरभूत व्योम amp_create_logical_link(काष्ठा l2cap_chan *chan)
अणु
पूर्ण

अटल अंतरभूत व्योम amp_disconnect_logical_link(काष्ठा hci_chan *hchan)
अणु
पूर्ण
#पूर्ण_अगर

व्योम amp_ग_लिखो_remote_assoc(काष्ठा hci_dev *hdev, u8 handle);
व्योम amp_ग_लिखो_rem_assoc_जारी(काष्ठा hci_dev *hdev, u8 handle);
व्योम amp_physical_cfm(काष्ठा hci_conn *bredr_hcon, काष्ठा hci_conn *hs_hcon);
व्योम amp_create_logical_link(काष्ठा l2cap_chan *chan);
व्योम amp_disconnect_logical_link(काष्ठा hci_chan *hchan);
व्योम amp_destroy_logical_link(काष्ठा hci_chan *hchan, u8 reason);

#पूर्ण_अगर /* __AMP_H */
