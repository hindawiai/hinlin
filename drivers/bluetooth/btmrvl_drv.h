<शैली गुरु>
/*
 * Marvell Bluetooth driver: global definitions & declarations
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
 *
 */

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <net/bluetooth/bluetooth.h>
#समावेश <linux/err.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of_irq.h>

#घोषणा BTM_HEADER_LEN			4
#घोषणा BTM_UPLD_SIZE			2312

/* Time to रुको until Host Sleep state change in millisecond */
#घोषणा WAIT_UNTIL_HS_STATE_CHANGED	msecs_to_jअगरfies(5000)
/* Time to रुको क्रम command response in millisecond */
#घोषणा WAIT_UNTIL_CMD_RESP		msecs_to_jअगरfies(5000)

क्रमागत rdwr_status अणु
	RDWR_STATUS_SUCCESS = 0,
	RDWR_STATUS_FAILURE = 1,
	RDWR_STATUS_DONE = 2
पूर्ण;

#घोषणा FW_DUMP_MAX_NAME_LEN    8
#घोषणा FW_DUMP_HOST_READY      0xEE
#घोषणा FW_DUMP_DONE            0xFF
#घोषणा FW_DUMP_READ_DONE       0xFE

काष्ठा memory_type_mapping अणु
	u8 mem_name[FW_DUMP_MAX_NAME_LEN];
	u8 *mem_ptr;
	u32 mem_size;
	u8 करोne_flag;
पूर्ण;

काष्ठा bपंचांगrvl_thपढ़ो अणु
	काष्ठा task_काष्ठा *task;
	रुको_queue_head_t रुको_q;
	व्योम *priv;
पूर्ण;

काष्ठा bपंचांगrvl_device अणु
	व्योम *card;
	काष्ठा hci_dev *hcidev;

	u8 dev_type;

	u8 tx_dnld_rdy;

	u8 psmode;
	u8 pscmd;
	u8 hsmode;
	u8 hscmd;

	/* Low byte is gap, high byte is GPIO */
	u16 gpio_gap;

	u8 hscfgcmd;
	u8 sendcmdflag;
पूर्ण;

काष्ठा bपंचांगrvl_adapter अणु
	व्योम *hw_regs_buf;
	u8 *hw_regs;
	u32 पूर्णांक_count;
	काष्ठा sk_buff_head tx_queue;
	u8 psmode;
	u8 ps_state;
	u8 hs_state;
	u8 wakeup_tries;
	रुको_queue_head_t cmd_रुको_q;
	रुको_queue_head_t event_hs_रुको_q;
	u8 cmd_complete;
	bool is_suspended;
	bool is_suspending;
पूर्ण;

काष्ठा bपंचांगrvl_निजी अणु
	काष्ठा bपंचांगrvl_device bपंचांगrvl_dev;
	काष्ठा bपंचांगrvl_adapter *adapter;
	काष्ठा bपंचांगrvl_thपढ़ो मुख्य_thपढ़ो;
	पूर्णांक (*hw_host_to_card)(काष्ठा bपंचांगrvl_निजी *priv,
				u8 *payload, u16 nb);
	पूर्णांक (*hw_wakeup_firmware)(काष्ठा bपंचांगrvl_निजी *priv);
	पूर्णांक (*hw_process_पूर्णांक_status)(काष्ठा bपंचांगrvl_निजी *priv);
	spinlock_t driver_lock;		/* spinlock used by driver */
#अगर_घोषित CONFIG_DEBUG_FS
	व्योम *debugfs_data;
#पूर्ण_अगर
	bool surprise_हटाओd;
पूर्ण;

#घोषणा MRVL_VENDOR_PKT			0xFE

/* Venकरोr specअगरic Bluetooth commands */
#घोषणा BT_CMD_PSCAN_WIN_REPORT_ENABLE	0xFC03
#घोषणा BT_CMD_ROUTE_SCO_TO_HOST	0xFC1D
#घोषणा BT_CMD_SET_BDADDR		0xFC22
#घोषणा BT_CMD_AUTO_SLEEP_MODE		0xFC23
#घोषणा BT_CMD_HOST_SLEEP_CONFIG	0xFC59
#घोषणा BT_CMD_HOST_SLEEP_ENABLE	0xFC5A
#घोषणा BT_CMD_MODULE_CFG_REQ		0xFC5B
#घोषणा BT_CMD_LOAD_CONFIG_DATA		0xFC61

/* Sub-commands: Module Bringup/Shutकरोwn Request/Response */
#घोषणा MODULE_BRINGUP_REQ		0xF1
#घोषणा MODULE_BROUGHT_UP		0x00
#घोषणा MODULE_ALREADY_UP		0x0C

#घोषणा MODULE_SHUTDOWN_REQ		0xF2

/* Venकरोr specअगरic Bluetooth events */
#घोषणा BT_EVENT_AUTO_SLEEP_MODE	0x23
#घोषणा BT_EVENT_HOST_SLEEP_CONFIG	0x59
#घोषणा BT_EVENT_HOST_SLEEP_ENABLE	0x5A
#घोषणा BT_EVENT_MODULE_CFG_REQ		0x5B
#घोषणा BT_EVENT_POWER_STATE		0x20

/* Bluetooth Power States */
#घोषणा BT_PS_ENABLE			0x02
#घोषणा BT_PS_DISABLE			0x03
#घोषणा BT_PS_SLEEP			0x01

/* Host Sleep states */
#घोषणा HS_ACTIVATED			0x01
#घोषणा HS_DEACTIVATED			0x00

/* Power Save modes */
#घोषणा PS_SLEEP			0x01
#घोषणा PS_AWAKE			0x00

#घोषणा BT_CAL_HDR_LEN			4
#घोषणा BT_CAL_DATA_SIZE		28

काष्ठा bपंचांगrvl_event अणु
	u8 ec;		/* event counter */
	u8 length;
	u8 data[4];
पूर्ण __packed;

/* Prototype of global function */

पूर्णांक bपंचांगrvl_रेजिस्टर_hdev(काष्ठा bपंचांगrvl_निजी *priv);
काष्ठा bपंचांगrvl_निजी *bपंचांगrvl_add_card(व्योम *card);
पूर्णांक bपंचांगrvl_हटाओ_card(काष्ठा bपंचांगrvl_निजी *priv);

व्योम bपंचांगrvl_पूर्णांकerrupt(काष्ठा bपंचांगrvl_निजी *priv);

bool bपंचांगrvl_check_evtpkt(काष्ठा bपंचांगrvl_निजी *priv, काष्ठा sk_buff *skb);
पूर्णांक bपंचांगrvl_process_event(काष्ठा bपंचांगrvl_निजी *priv, काष्ठा sk_buff *skb);

पूर्णांक bपंचांगrvl_send_module_cfg_cmd(काष्ठा bपंचांगrvl_निजी *priv, u8 subcmd);
पूर्णांक bपंचांगrvl_pscan_winकरोw_reporting(काष्ठा bपंचांगrvl_निजी *priv, u8 subcmd);
पूर्णांक bपंचांगrvl_send_hscfg_cmd(काष्ठा bपंचांगrvl_निजी *priv);
पूर्णांक bपंचांगrvl_enable_ps(काष्ठा bपंचांगrvl_निजी *priv);
पूर्णांक bपंचांगrvl_prepare_command(काष्ठा bपंचांगrvl_निजी *priv);
पूर्णांक bपंचांगrvl_enable_hs(काष्ठा bपंचांगrvl_निजी *priv);

#अगर_घोषित CONFIG_DEBUG_FS
व्योम bपंचांगrvl_debugfs_init(काष्ठा hci_dev *hdev);
व्योम bपंचांगrvl_debugfs_हटाओ(काष्ठा hci_dev *hdev);
#पूर्ण_अगर
