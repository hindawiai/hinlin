<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __TARGET_USB_GADGET_H__
#घोषणा __TARGET_USB_GADGET_H__

#समावेश <linux/kref.h>
/* #समावेश <linux/usb/uas.h> */
#समावेश <linux/usb/composite.h>
#समावेश <linux/usb/uas.h>
#समावेश <linux/usb/storage.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>

#घोषणा USBG_NAMELEN 32

#घोषणा fuas_to_gadget(f)	(f->function.config->cdev->gadget)
#घोषणा UASP_SS_EP_COMP_LOG_STREAMS 4
#घोषणा UASP_SS_EP_COMP_NUM_STREAMS (1 << UASP_SS_EP_COMP_LOG_STREAMS)

क्रमागत अणु
	USB_G_STR_INT_UAS = 0,
	USB_G_STR_INT_BBB,
पूर्ण;

#घोषणा USB_G_ALT_INT_BBB       0
#घोषणा USB_G_ALT_INT_UAS       1

#घोषणा USB_G_DEFAULT_SESSION_TAGS	128

काष्ठा tcm_usbg_nexus अणु
	काष्ठा se_session *tvn_se_sess;
पूर्ण;

काष्ठा usbg_tpg अणु
	काष्ठा mutex tpg_mutex;
	/* SAS port target portal group tag क्रम TCM */
	u16 tport_tpgt;
	/* Poपूर्णांकer back to usbg_tport */
	काष्ठा usbg_tport *tport;
	काष्ठा workqueue_काष्ठा *workqueue;
	/* Returned by usbg_make_tpg() */
	काष्ठा se_portal_group se_tpg;
	u32 gadget_connect;
	काष्ठा tcm_usbg_nexus *tpg_nexus;
	atomic_t tpg_port_count;

	काष्ठा usb_function_instance *fi;
पूर्ण;

काष्ठा usbg_tport अणु
	/* Binary World Wide unique Port Name क्रम SAS Target port */
	u64 tport_wwpn;
	/* ASCII क्रमmatted WWPN क्रम SAS Target port */
	अक्षर tport_name[USBG_NAMELEN];
	/* Returned by usbg_make_tport() */
	काष्ठा se_wwn tport_wwn;
पूर्ण;

क्रमागत uas_state अणु
	UASP_SEND_DATA,
	UASP_RECEIVE_DATA,
	UASP_SEND_STATUS,
	UASP_QUEUE_COMMAND,
पूर्ण;

#घोषणा USBG_MAX_CMD    64
काष्ठा usbg_cmd अणु
	/* common */
	u8 cmd_buf[USBG_MAX_CMD];
	u32 data_len;
	काष्ठा work_काष्ठा work;
	पूर्णांक unpacked_lun;
	काष्ठा se_cmd se_cmd;
	व्योम *data_buf; /* used अगर no sg support available */
	काष्ठा f_uas *fu;
	काष्ठा completion ग_लिखो_complete;
	काष्ठा kref ref;

	/* UAS only */
	u16 tag;
	u16 prio_attr;
	काष्ठा sense_iu sense_iu;
	क्रमागत uas_state state;
	काष्ठा uas_stream *stream;

	/* BOT only */
	__le32 bot_tag;
	अचिन्हित पूर्णांक csw_code;
	अचिन्हित is_पढ़ो:1;

पूर्ण;

काष्ठा uas_stream अणु
	काष्ठा usb_request	*req_in;
	काष्ठा usb_request	*req_out;
	काष्ठा usb_request	*req_status;
पूर्ण;

काष्ठा usbg_cdb अणु
	काष्ठा usb_request	*req;
	व्योम			*buf;
पूर्ण;

काष्ठा bot_status अणु
	काष्ठा usb_request	*req;
	काष्ठा bulk_cs_wrap	csw;
पूर्ण;

काष्ठा f_uas अणु
	काष्ठा usbg_tpg		*tpg;
	काष्ठा usb_function	function;
	u16			अगरace;

	u32			flags;
#घोषणा USBG_ENABLED		(1 << 0)
#घोषणा USBG_IS_UAS		(1 << 1)
#घोषणा USBG_USE_STREAMS	(1 << 2)
#घोषणा USBG_IS_BOT		(1 << 3)
#घोषणा USBG_BOT_CMD_PEND	(1 << 4)

	काष्ठा usbg_cdb		cmd;
	काष्ठा usb_ep		*ep_in;
	काष्ठा usb_ep		*ep_out;

	/* UAS */
	काष्ठा usb_ep		*ep_status;
	काष्ठा usb_ep		*ep_cmd;
	काष्ठा uas_stream	stream[UASP_SS_EP_COMP_NUM_STREAMS];

	/* BOT */
	काष्ठा bot_status	bot_status;
	काष्ठा usb_request	*bot_req_in;
	काष्ठा usb_request	*bot_req_out;
पूर्ण;

#पूर्ण_अगर /* __TARGET_USB_GADGET_H__ */
