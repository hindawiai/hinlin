<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित HOSTAP_H
#घोषणा HOSTAP_H

#समावेश <linux/ethtool.h>
#समावेश <linux/kernel.h>

#समावेश "hostap_wlan.h"
#समावेश "hostap_ap.h"

अटल स्थिर दीर्घ __maybe_unused freq_list[] = अणु
	2412, 2417, 2422, 2427, 2432, 2437, 2442,
	2447, 2452, 2457, 2462, 2467, 2472, 2484
पूर्ण;
#घोषणा FREQ_COUNT ARRAY_SIZE(freq_list)

/* hostap.c */

बाह्य काष्ठा proc_dir_entry *hostap_proc;

u16 hostap_tx_callback_रेजिस्टर(local_info_t *local,
				व्योम (*func)(काष्ठा sk_buff *, पूर्णांक ok, व्योम *),
				व्योम *data);
पूर्णांक hostap_tx_callback_unरेजिस्टर(local_info_t *local, u16 idx);
पूर्णांक hostap_set_word(काष्ठा net_device *dev, पूर्णांक rid, u16 val);
पूर्णांक hostap_set_string(काष्ठा net_device *dev, पूर्णांक rid, स्थिर अक्षर *val);
u16 hostap_get_porttype(local_info_t *local);
पूर्णांक hostap_set_encryption(local_info_t *local);
पूर्णांक hostap_set_antsel(local_info_t *local);
पूर्णांक hostap_set_roaming(local_info_t *local);
पूर्णांक hostap_set_auth_algs(local_info_t *local);
व्योम hostap_dump_rx_header(स्थिर अक्षर *name,
			   स्थिर काष्ठा hfa384x_rx_frame *rx);
व्योम hostap_dump_tx_header(स्थिर अक्षर *name,
			   स्थिर काष्ठा hfa384x_tx_frame *tx);
बाह्य स्थिर काष्ठा header_ops hostap_80211_ops;
पूर्णांक hostap_80211_get_hdrlen(__le16 fc);
काष्ठा net_device_stats *hostap_get_stats(काष्ठा net_device *dev);
व्योम hostap_setup_dev(काष्ठा net_device *dev, local_info_t *local,
		      पूर्णांक type);
व्योम hostap_set_multicast_list_queue(काष्ठा work_काष्ठा *work);
पूर्णांक hostap_set_hostapd(local_info_t *local, पूर्णांक val, पूर्णांक rtnl_locked);
पूर्णांक hostap_set_hostapd_sta(local_info_t *local, पूर्णांक val, पूर्णांक rtnl_locked);
व्योम hostap_cleanup(local_info_t *local);
व्योम hostap_cleanup_handler(व्योम *data);
काष्ठा net_device * hostap_add_पूर्णांकerface(काष्ठा local_info *local,
					 पूर्णांक type, पूर्णांक rtnl_locked,
					 स्थिर अक्षर *prefix, स्थिर अक्षर *name);
व्योम hostap_हटाओ_पूर्णांकerface(काष्ठा net_device *dev, पूर्णांक rtnl_locked,
			     पूर्णांक हटाओ_from_list);
पूर्णांक prism2_update_comms_qual(काष्ठा net_device *dev);
पूर्णांक prism2_sta_send_mgmt(local_info_t *local, u8 *dst, u16 stype,
			 u8 *body, माप_प्रकार bodylen);
पूर्णांक prism2_sta_deauth(local_info_t *local, u16 reason);
पूर्णांक prism2_wds_add(local_info_t *local, u8 *remote_addr,
		   पूर्णांक rtnl_locked);
पूर्णांक prism2_wds_del(local_info_t *local, u8 *remote_addr,
		   पूर्णांक rtnl_locked, पूर्णांक करो_not_हटाओ);


/* hostap_ap.c */

पूर्णांक ap_control_add_mac(काष्ठा mac_restrictions *mac_restrictions, u8 *mac);
पूर्णांक ap_control_del_mac(काष्ठा mac_restrictions *mac_restrictions, u8 *mac);
व्योम ap_control_flush_macs(काष्ठा mac_restrictions *mac_restrictions);
पूर्णांक ap_control_kick_mac(काष्ठा ap_data *ap, काष्ठा net_device *dev, u8 *mac);
व्योम ap_control_kickall(काष्ठा ap_data *ap);
व्योम * ap_crypt_get_ptrs(काष्ठा ap_data *ap, u8 *addr, पूर्णांक permanent,
			 काष्ठा lib80211_crypt_data ***crypt);
पूर्णांक prism2_ap_get_sta_qual(local_info_t *local, काष्ठा sockaddr addr[],
			   काष्ठा iw_quality qual[], पूर्णांक buf_size,
			   पूर्णांक aplist);
पूर्णांक prism2_ap_translate_scan(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info, अक्षर *buffer);
पूर्णांक prism2_hostapd(काष्ठा ap_data *ap, काष्ठा prism2_hostapd_param *param);


/* hostap_proc.c */

व्योम hostap_init_proc(local_info_t *local);
व्योम hostap_हटाओ_proc(local_info_t *local);


/* hostap_info.c */

व्योम hostap_info_init(local_info_t *local);
व्योम hostap_info_process(local_info_t *local, काष्ठा sk_buff *skb);


/* hostap_ioctl.c */

बाह्य स्थिर काष्ठा iw_handler_def hostap_iw_handler_def;
बाह्य स्थिर काष्ठा ethtool_ops prism2_ethtool_ops;

पूर्णांक hostap_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);


#पूर्ण_अगर /* HOSTAP_H */
