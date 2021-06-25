<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LBS_IF_USB_H
#घोषणा _LBS_IF_USB_H

#समावेश <linux/रुको.h>
#समावेश <linux/समयr.h>

काष्ठा lbs_निजी;

/*
 * This file contains definition क्रम USB पूर्णांकerface.
 */
#घोषणा CMD_TYPE_REQUEST		0xF00DFACE
#घोषणा CMD_TYPE_DATA			0xBEADC0DE
#घोषणा CMD_TYPE_INDICATION		0xBEEFFACE

#घोषणा IPFIELD_ALIGN_OFFSET		2

#घोषणा BOOT_CMD_FW_BY_USB		0x01
#घोषणा BOOT_CMD_FW_IN_EEPROM		0x02
#घोषणा BOOT_CMD_UPDATE_BOOT2		0x03
#घोषणा BOOT_CMD_UPDATE_FW		0x04
#घोषणा BOOT_CMD_MAGIC_NUMBER		0x4C56524D   /* LVRM */

काष्ठा bootcmd
अणु
	__le32	magic;
	uपूर्णांक8_t	cmd;
	uपूर्णांक8_t	pad[11];
पूर्ण;

#घोषणा BOOT_CMD_RESP_OK		0x0001
#घोषणा BOOT_CMD_RESP_FAIL		0x0000
#घोषणा BOOT_CMD_RESP_NOT_SUPPORTED	0x0002

काष्ठा bootcmdresp
अणु
	__le32	magic;
	uपूर्णांक8_t	cmd;
	uपूर्णांक8_t	result;
	uपूर्णांक8_t	pad[2];
पूर्ण;

/* USB card description काष्ठाure*/
काष्ठा अगर_usb_card अणु
	काष्ठा usb_device *udev;
	uपूर्णांक32_t model;  /* MODEL_* */
	काष्ठा urb *rx_urb, *tx_urb;
	काष्ठा lbs_निजी *priv;

	काष्ठा sk_buff *rx_skb;

	uपूर्णांक8_t ep_in;
	uपूर्णांक8_t ep_out;

	/* bootcmdresp == 0 means command is pending
	 * bootcmdresp < 0 means error
	 * bootcmdresp > 0 is a BOOT_CMD_RESP_* from firmware
	 */
	पूर्णांक8_t bootcmdresp;

	पूर्णांक ep_in_size;

	व्योम *ep_out_buf;
	पूर्णांक ep_out_size;

	स्थिर काष्ठा firmware *fw;
	काष्ठा समयr_list fw_समयout;
	रुको_queue_head_t fw_wq;
	uपूर्णांक32_t fwseqnum;
	uपूर्णांक32_t totalbytes;
	uपूर्णांक32_t fwlastblksent;
	uपूर्णांक8_t CRC_OK;
	uपूर्णांक8_t fwdnlकरोver;
	uपूर्णांक8_t fwfinalblk;
	uपूर्णांक8_t surprise_हटाओd;

	__le16 boot2_version;
पूर्ण;

/* fwheader */
काष्ठा fwheader अणु
	__le32 dnldcmd;
	__le32 baseaddr;
	__le32 datalength;
	__le32 CRC;
पूर्ण;

#घोषणा FW_MAX_DATA_BLK_SIZE	600
/* FWData */
काष्ठा fwdata अणु
	काष्ठा fwheader hdr;
	__le32 seqnum;
	uपूर्णांक8_t data[];
पूर्ण;

/* fwsyncheader */
काष्ठा fwsyncheader अणु
	__le32 cmd;
	__le32 seqnum;
पूर्ण;

#घोषणा FW_HAS_DATA_TO_RECV		0x00000001
#घोषणा FW_HAS_LAST_BLOCK		0x00000004


#पूर्ण_अगर
