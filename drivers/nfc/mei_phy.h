<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LOCAL_MEI_PHY_H_
#घोषणा __LOCAL_MEI_PHY_H_

#समावेश <linux/mei_cl_bus.h>
#समावेश <net/nfc/hci.h>
#समावेश <linux/uuid.h>

#घोषणा MEI_NFC_UUID UUID_LE(0x0bb17a78, 0x2a8e, 0x4c50, \
		0x94, 0xd4, 0x50, 0x26, 0x67, 0x23, 0x77, 0x5c)
#घोषणा MEI_NFC_HEADER_SIZE 10
#घोषणा MEI_NFC_MAX_HCI_PAYLOAD 300

/**
 * काष्ठा nfc_mei_phy
 *
 * @cldev: mei client device
 * @hdev:   nfc hci device

 * @send_wq: send completion रुको queue
 * @fw_ivn: NFC Interface Version Number
 * @venकरोr_id: NFC manufacturer ID
 * @radio_type: NFC radio type
 * @reserved: reserved क्रम alignment
 * @req_id:  message counter
 * @recv_req_id: reception message counter
 * @घातered: the device is in घातered state
 * @hard_fault: < 0 अगर hardware error occurred
 *    and prevents normal operation.
 */
काष्ठा nfc_mei_phy अणु
	काष्ठा mei_cl_device *cldev;
	काष्ठा nfc_hci_dev *hdev;

	रुको_queue_head_t send_wq;
	u8 fw_ivn;
	u8 venकरोr_id;
	u8 radio_type;
	u8 reserved;

	u16 req_id;
	u16 recv_req_id;

	पूर्णांक घातered;
	पूर्णांक hard_fault;
पूर्ण;

बाह्य काष्ठा nfc_phy_ops mei_phy_ops;

काष्ठा nfc_mei_phy *nfc_mei_phy_alloc(काष्ठा mei_cl_device *device);
व्योम nfc_mei_phy_मुक्त(काष्ठा nfc_mei_phy *phy);

#पूर्ण_अगर /* __LOCAL_MEI_PHY_H_ */
