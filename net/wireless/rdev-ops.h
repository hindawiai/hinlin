<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __CFG80211_RDEV_OPS
#घोषणा __CFG80211_RDEV_OPS

#समावेश <linux/rtnetlink.h>
#समावेश <net/cfg80211.h>
#समावेश "core.h"
#समावेश "trace.h"

अटल अंतरभूत पूर्णांक rdev_suspend(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा cfg80211_wowlan *wowlan)
अणु
	पूर्णांक ret;
	trace_rdev_suspend(&rdev->wiphy, wowlan);
	ret = rdev->ops->suspend(&rdev->wiphy, wowlan);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_resume(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	पूर्णांक ret;
	trace_rdev_resume(&rdev->wiphy);
	ret = rdev->ops->resume(&rdev->wiphy);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम rdev_set_wakeup(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   bool enabled)
अणु
	trace_rdev_set_wakeup(&rdev->wiphy, enabled);
	rdev->ops->set_wakeup(&rdev->wiphy, enabled);
	trace_rdev_वापस_व्योम(&rdev->wiphy);
पूर्ण

अटल अंतरभूत काष्ठा wireless_dev
*rdev_add_भव_पूर्णांकf(काष्ठा cfg80211_रेजिस्टरed_device *rdev, अक्षर *name,
		       अचिन्हित अक्षर name_assign_type,
		       क्रमागत nl80211_अगरtype type,
		       काष्ठा vअगर_params *params)
अणु
	काष्ठा wireless_dev *ret;
	trace_rdev_add_भव_पूर्णांकf(&rdev->wiphy, name, type);
	ret = rdev->ops->add_भव_पूर्णांकf(&rdev->wiphy, name, name_assign_type,
					  type, params);
	trace_rdev_वापस_wdev(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_del_भव_पूर्णांकf(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		      काष्ठा wireless_dev *wdev)
अणु
	पूर्णांक ret;
	trace_rdev_del_भव_पूर्णांकf(&rdev->wiphy, wdev);
	ret = rdev->ops->del_भव_पूर्णांकf(&rdev->wiphy, wdev);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_change_भव_पूर्णांकf(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा net_device *dev, क्रमागत nl80211_अगरtype type,
			 काष्ठा vअगर_params *params)
अणु
	पूर्णांक ret;
	trace_rdev_change_भव_पूर्णांकf(&rdev->wiphy, dev, type);
	ret = rdev->ops->change_भव_पूर्णांकf(&rdev->wiphy, dev, type, params);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_add_key(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा net_device *netdev, u8 key_index,
			       bool pairwise, स्थिर u8 *mac_addr,
			       काष्ठा key_params *params)
अणु
	पूर्णांक ret;
	trace_rdev_add_key(&rdev->wiphy, netdev, key_index, pairwise,
			   mac_addr, params->mode);
	ret = rdev->ops->add_key(&rdev->wiphy, netdev, key_index, pairwise,
				  mac_addr, params);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_get_key(काष्ठा cfg80211_रेजिस्टरed_device *rdev, काष्ठा net_device *netdev,
	     u8 key_index, bool pairwise, स्थिर u8 *mac_addr, व्योम *cookie,
	     व्योम (*callback)(व्योम *cookie, काष्ठा key_params*))
अणु
	पूर्णांक ret;
	trace_rdev_get_key(&rdev->wiphy, netdev, key_index, pairwise, mac_addr);
	ret = rdev->ops->get_key(&rdev->wiphy, netdev, key_index, pairwise,
				  mac_addr, cookie, callback);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_del_key(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा net_device *netdev, u8 key_index,
			       bool pairwise, स्थिर u8 *mac_addr)
अणु
	पूर्णांक ret;
	trace_rdev_del_key(&rdev->wiphy, netdev, key_index, pairwise, mac_addr);
	ret = rdev->ops->del_key(&rdev->wiphy, netdev, key_index, pairwise,
				  mac_addr);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_शेष_key(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		     काष्ठा net_device *netdev, u8 key_index, bool unicast,
		     bool multicast)
अणु
	पूर्णांक ret;
	trace_rdev_set_शेष_key(&rdev->wiphy, netdev, key_index,
				   unicast, multicast);
	ret = rdev->ops->set_शेष_key(&rdev->wiphy, netdev, key_index,
					  unicast, multicast);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_शेष_mgmt_key(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा net_device *netdev, u8 key_index)
अणु
	पूर्णांक ret;
	trace_rdev_set_शेष_mgmt_key(&rdev->wiphy, netdev, key_index);
	ret = rdev->ops->set_शेष_mgmt_key(&rdev->wiphy, netdev,
					       key_index);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_शेष_beacon_key(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			    काष्ठा net_device *netdev, u8 key_index)
अणु
	पूर्णांक ret;

	trace_rdev_set_शेष_beacon_key(&rdev->wiphy, netdev, key_index);
	ret = rdev->ops->set_शेष_beacon_key(&rdev->wiphy, netdev,
						key_index);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_start_ap(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				काष्ठा net_device *dev,
				काष्ठा cfg80211_ap_settings *settings)
अणु
	पूर्णांक ret;
	trace_rdev_start_ap(&rdev->wiphy, dev, settings);
	ret = rdev->ops->start_ap(&rdev->wiphy, dev, settings);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_change_beacon(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				     काष्ठा net_device *dev,
				     काष्ठा cfg80211_beacon_data *info)
अणु
	पूर्णांक ret;
	trace_rdev_change_beacon(&rdev->wiphy, dev, info);
	ret = rdev->ops->change_beacon(&rdev->wiphy, dev, info);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_stop_ap(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा net_device *dev)
अणु
	पूर्णांक ret;
	trace_rdev_stop_ap(&rdev->wiphy, dev);
	ret = rdev->ops->stop_ap(&rdev->wiphy, dev);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_add_station(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   काष्ठा net_device *dev, u8 *mac,
				   काष्ठा station_parameters *params)
अणु
	पूर्णांक ret;
	trace_rdev_add_station(&rdev->wiphy, dev, mac, params);
	ret = rdev->ops->add_station(&rdev->wiphy, dev, mac, params);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_del_station(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   काष्ठा net_device *dev,
				   काष्ठा station_del_parameters *params)
अणु
	पूर्णांक ret;
	trace_rdev_del_station(&rdev->wiphy, dev, params);
	ret = rdev->ops->del_station(&rdev->wiphy, dev, params);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_change_station(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				      काष्ठा net_device *dev, u8 *mac,
				      काष्ठा station_parameters *params)
अणु
	पूर्णांक ret;
	trace_rdev_change_station(&rdev->wiphy, dev, mac, params);
	ret = rdev->ops->change_station(&rdev->wiphy, dev, mac, params);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_get_station(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   काष्ठा net_device *dev, स्थिर u8 *mac,
				   काष्ठा station_info *sinfo)
अणु
	पूर्णांक ret;
	trace_rdev_get_station(&rdev->wiphy, dev, mac);
	ret = rdev->ops->get_station(&rdev->wiphy, dev, mac, sinfo);
	trace_rdev_वापस_पूर्णांक_station_info(&rdev->wiphy, ret, sinfo);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_dump_station(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				    काष्ठा net_device *dev, पूर्णांक idx, u8 *mac,
				    काष्ठा station_info *sinfo)
अणु
	पूर्णांक ret;
	trace_rdev_dump_station(&rdev->wiphy, dev, idx, mac);
	ret = rdev->ops->dump_station(&rdev->wiphy, dev, idx, mac, sinfo);
	trace_rdev_वापस_पूर्णांक_station_info(&rdev->wiphy, ret, sinfo);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_add_mpath(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा net_device *dev, u8 *dst, u8 *next_hop)
अणु
	पूर्णांक ret;
	trace_rdev_add_mpath(&rdev->wiphy, dev, dst, next_hop);
	ret = rdev->ops->add_mpath(&rdev->wiphy, dev, dst, next_hop);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_del_mpath(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा net_device *dev, u8 *dst)
अणु
	पूर्णांक ret;
	trace_rdev_del_mpath(&rdev->wiphy, dev, dst);
	ret = rdev->ops->del_mpath(&rdev->wiphy, dev, dst);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_change_mpath(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				    काष्ठा net_device *dev, u8 *dst,
				    u8 *next_hop)
अणु
	पूर्णांक ret;
	trace_rdev_change_mpath(&rdev->wiphy, dev, dst, next_hop);
	ret = rdev->ops->change_mpath(&rdev->wiphy, dev, dst, next_hop);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_get_mpath(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा net_device *dev, u8 *dst, u8 *next_hop,
				 काष्ठा mpath_info *pinfo)
अणु
	पूर्णांक ret;
	trace_rdev_get_mpath(&rdev->wiphy, dev, dst, next_hop);
	ret = rdev->ops->get_mpath(&rdev->wiphy, dev, dst, next_hop, pinfo);
	trace_rdev_वापस_पूर्णांक_mpath_info(&rdev->wiphy, ret, pinfo);
	वापस ret;

पूर्ण

अटल अंतरभूत पूर्णांक rdev_get_mpp(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा net_device *dev, u8 *dst, u8 *mpp,
			       काष्ठा mpath_info *pinfo)
अणु
	पूर्णांक ret;

	trace_rdev_get_mpp(&rdev->wiphy, dev, dst, mpp);
	ret = rdev->ops->get_mpp(&rdev->wiphy, dev, dst, mpp, pinfo);
	trace_rdev_वापस_पूर्णांक_mpath_info(&rdev->wiphy, ret, pinfo);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_dump_mpath(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				  काष्ठा net_device *dev, पूर्णांक idx, u8 *dst,
				  u8 *next_hop, काष्ठा mpath_info *pinfo)

अणु
	पूर्णांक ret;
	trace_rdev_dump_mpath(&rdev->wiphy, dev, idx, dst, next_hop);
	ret = rdev->ops->dump_mpath(&rdev->wiphy, dev, idx, dst, next_hop,
				    pinfo);
	trace_rdev_वापस_पूर्णांक_mpath_info(&rdev->wiphy, ret, pinfo);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_dump_mpp(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				काष्ठा net_device *dev, पूर्णांक idx, u8 *dst,
				u8 *mpp, काष्ठा mpath_info *pinfo)

अणु
	पूर्णांक ret;

	trace_rdev_dump_mpp(&rdev->wiphy, dev, idx, dst, mpp);
	ret = rdev->ops->dump_mpp(&rdev->wiphy, dev, idx, dst, mpp, pinfo);
	trace_rdev_वापस_पूर्णांक_mpath_info(&rdev->wiphy, ret, pinfo);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_get_mesh_config(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		     काष्ठा net_device *dev, काष्ठा mesh_config *conf)
अणु
	पूर्णांक ret;
	trace_rdev_get_mesh_config(&rdev->wiphy, dev);
	ret = rdev->ops->get_mesh_config(&rdev->wiphy, dev, conf);
	trace_rdev_वापस_पूर्णांक_mesh_config(&rdev->wiphy, ret, conf);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_update_mesh_config(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			काष्ठा net_device *dev, u32 mask,
			स्थिर काष्ठा mesh_config *nconf)
अणु
	पूर्णांक ret;
	trace_rdev_update_mesh_config(&rdev->wiphy, dev, mask, nconf);
	ret = rdev->ops->update_mesh_config(&rdev->wiphy, dev, mask, nconf);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_join_mesh(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा net_device *dev,
				 स्थिर काष्ठा mesh_config *conf,
				 स्थिर काष्ठा mesh_setup *setup)
अणु
	पूर्णांक ret;
	trace_rdev_join_mesh(&rdev->wiphy, dev, conf, setup);
	ret = rdev->ops->join_mesh(&rdev->wiphy, dev, conf, setup);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण


अटल अंतरभूत पूर्णांक rdev_leave_mesh(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				  काष्ठा net_device *dev)
अणु
	पूर्णांक ret;
	trace_rdev_leave_mesh(&rdev->wiphy, dev);
	ret = rdev->ops->leave_mesh(&rdev->wiphy, dev);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_join_ocb(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				काष्ठा net_device *dev,
				काष्ठा ocb_setup *setup)
अणु
	पूर्णांक ret;
	trace_rdev_join_ocb(&rdev->wiphy, dev, setup);
	ret = rdev->ops->join_ocb(&rdev->wiphy, dev, setup);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_leave_ocb(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा net_device *dev)
अणु
	पूर्णांक ret;
	trace_rdev_leave_ocb(&rdev->wiphy, dev);
	ret = rdev->ops->leave_ocb(&rdev->wiphy, dev);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_change_bss(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				  काष्ठा net_device *dev,
				  काष्ठा bss_parameters *params)

अणु
	पूर्णांक ret;
	trace_rdev_change_bss(&rdev->wiphy, dev, params);
	ret = rdev->ops->change_bss(&rdev->wiphy, dev, params);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_set_txq_params(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				      काष्ठा net_device *dev,
				      काष्ठा ieee80211_txq_params *params)

अणु
	पूर्णांक ret;
	trace_rdev_set_txq_params(&rdev->wiphy, dev, params);
	ret = rdev->ops->set_txq_params(&rdev->wiphy, dev, params);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_libertas_set_mesh_channel(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा net_device *dev,
			       काष्ठा ieee80211_channel *chan)
अणु
	पूर्णांक ret;
	trace_rdev_libertas_set_mesh_channel(&rdev->wiphy, dev, chan);
	ret = rdev->ops->libertas_set_mesh_channel(&rdev->wiphy, dev, chan);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_monitor_channel(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा cfg80211_chan_def *chandef)
अणु
	पूर्णांक ret;
	trace_rdev_set_monitor_channel(&rdev->wiphy, chandef);
	ret = rdev->ops->set_monitor_channel(&rdev->wiphy, chandef);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_scan(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			    काष्ठा cfg80211_scan_request *request)
अणु
	पूर्णांक ret;
	trace_rdev_scan(&rdev->wiphy, request);
	ret = rdev->ops->scan(&rdev->wiphy, request);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम rdev_पात_scan(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   काष्ठा wireless_dev *wdev)
अणु
	trace_rdev_पात_scan(&rdev->wiphy, wdev);
	rdev->ops->पात_scan(&rdev->wiphy, wdev);
	trace_rdev_वापस_व्योम(&rdev->wiphy);
पूर्ण

अटल अंतरभूत पूर्णांक rdev_auth(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			    काष्ठा net_device *dev,
			    काष्ठा cfg80211_auth_request *req)
अणु
	पूर्णांक ret;
	trace_rdev_auth(&rdev->wiphy, dev, req);
	ret = rdev->ops->auth(&rdev->wiphy, dev, req);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_assoc(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			     काष्ठा net_device *dev,
			     काष्ठा cfg80211_assoc_request *req)
अणु
	पूर्णांक ret;
	trace_rdev_assoc(&rdev->wiphy, dev, req);
	ret = rdev->ops->assoc(&rdev->wiphy, dev, req);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_deauth(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			      काष्ठा net_device *dev,
			      काष्ठा cfg80211_deauth_request *req)
अणु
	पूर्णांक ret;
	trace_rdev_deauth(&rdev->wiphy, dev, req);
	ret = rdev->ops->deauth(&rdev->wiphy, dev, req);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_disassoc(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				काष्ठा net_device *dev,
				काष्ठा cfg80211_disassoc_request *req)
अणु
	पूर्णांक ret;
	trace_rdev_disassoc(&rdev->wiphy, dev, req);
	ret = rdev->ops->disassoc(&rdev->wiphy, dev, req);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_connect(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा net_device *dev,
			       काष्ठा cfg80211_connect_params *sme)
अणु
	पूर्णांक ret;
	trace_rdev_connect(&rdev->wiphy, dev, sme);
	ret = rdev->ops->connect(&rdev->wiphy, dev, sme);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_update_connect_params(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			   काष्ठा net_device *dev,
			   काष्ठा cfg80211_connect_params *sme, u32 changed)
अणु
	पूर्णांक ret;
	trace_rdev_update_connect_params(&rdev->wiphy, dev, sme, changed);
	ret = rdev->ops->update_connect_params(&rdev->wiphy, dev, sme, changed);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_disconnect(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				  काष्ठा net_device *dev, u16 reason_code)
अणु
	पूर्णांक ret;
	trace_rdev_disconnect(&rdev->wiphy, dev, reason_code);
	ret = rdev->ops->disconnect(&rdev->wiphy, dev, reason_code);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_join_ibss(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा net_device *dev,
				 काष्ठा cfg80211_ibss_params *params)
अणु
	पूर्णांक ret;
	trace_rdev_join_ibss(&rdev->wiphy, dev, params);
	ret = rdev->ops->join_ibss(&rdev->wiphy, dev, params);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_leave_ibss(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				  काष्ठा net_device *dev)
अणु
	पूर्णांक ret;
	trace_rdev_leave_ibss(&rdev->wiphy, dev);
	ret = rdev->ops->leave_ibss(&rdev->wiphy, dev);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_wiphy_params(काष्ठा cfg80211_रेजिस्टरed_device *rdev, u32 changed)
अणु
	पूर्णांक ret;

	अगर (!rdev->ops->set_wiphy_params)
		वापस -EOPNOTSUPP;

	trace_rdev_set_wiphy_params(&rdev->wiphy, changed);
	ret = rdev->ops->set_wiphy_params(&rdev->wiphy, changed);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_set_tx_घातer(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				    काष्ठा wireless_dev *wdev,
				    क्रमागत nl80211_tx_घातer_setting type, पूर्णांक mbm)
अणु
	पूर्णांक ret;
	trace_rdev_set_tx_घातer(&rdev->wiphy, wdev, type, mbm);
	ret = rdev->ops->set_tx_घातer(&rdev->wiphy, wdev, type, mbm);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_get_tx_घातer(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				    काष्ठा wireless_dev *wdev, पूर्णांक *dbm)
अणु
	पूर्णांक ret;
	trace_rdev_get_tx_घातer(&rdev->wiphy, wdev);
	ret = rdev->ops->get_tx_घातer(&rdev->wiphy, wdev, dbm);
	trace_rdev_वापस_पूर्णांक_पूर्णांक(&rdev->wiphy, ret, *dbm);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_multicast_to_unicast(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			      काष्ठा net_device *dev,
			      स्थिर bool enabled)
अणु
	पूर्णांक ret;
	trace_rdev_set_multicast_to_unicast(&rdev->wiphy, dev, enabled);
	ret = rdev->ops->set_multicast_to_unicast(&rdev->wiphy, dev, enabled);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_get_txq_stats(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		   काष्ठा wireless_dev *wdev,
		   काष्ठा cfg80211_txq_stats *txqstats)
अणु
	पूर्णांक ret;
	trace_rdev_get_txq_stats(&rdev->wiphy, wdev);
	ret = rdev->ops->get_txq_stats(&rdev->wiphy, wdev, txqstats);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम rdev_rfसमाप्त_poll(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	trace_rdev_rfसमाप्त_poll(&rdev->wiphy);
	rdev->ops->rfसमाप्त_poll(&rdev->wiphy);
	trace_rdev_वापस_व्योम(&rdev->wiphy);
पूर्ण


#अगर_घोषित CONFIG_NL80211_TESTMODE
अटल अंतरभूत पूर्णांक rdev_tesपंचांगode_cmd(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				    काष्ठा wireless_dev *wdev,
				    व्योम *data, पूर्णांक len)
अणु
	पूर्णांक ret;
	trace_rdev_tesपंचांगode_cmd(&rdev->wiphy, wdev);
	ret = rdev->ops->tesपंचांगode_cmd(&rdev->wiphy, wdev, data, len);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_tesपंचांगode_dump(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				     काष्ठा sk_buff *skb,
				     काष्ठा netlink_callback *cb, व्योम *data,
				     पूर्णांक len)
अणु
	पूर्णांक ret;
	trace_rdev_tesपंचांगode_dump(&rdev->wiphy);
	ret = rdev->ops->tesपंचांगode_dump(&rdev->wiphy, skb, cb, data, len);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक
rdev_set_bitrate_mask(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		      काष्ठा net_device *dev, स्थिर u8 *peer,
		      स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	पूर्णांक ret;
	trace_rdev_set_bitrate_mask(&rdev->wiphy, dev, peer, mask);
	ret = rdev->ops->set_bitrate_mask(&rdev->wiphy, dev, peer, mask);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_dump_survey(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   काष्ठा net_device *netdev, पूर्णांक idx,
				   काष्ठा survey_info *info)
अणु
	पूर्णांक ret;
	trace_rdev_dump_survey(&rdev->wiphy, netdev, idx);
	ret = rdev->ops->dump_survey(&rdev->wiphy, netdev, idx, info);
	अगर (ret < 0)
		trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	अन्यथा
		trace_rdev_वापस_पूर्णांक_survey_info(&rdev->wiphy, ret, info);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_set_pmksa(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा net_device *netdev,
				 काष्ठा cfg80211_pmksa *pmksa)
अणु
	पूर्णांक ret;
	trace_rdev_set_pmksa(&rdev->wiphy, netdev, pmksa);
	ret = rdev->ops->set_pmksa(&rdev->wiphy, netdev, pmksa);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_del_pmksa(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा net_device *netdev,
				 काष्ठा cfg80211_pmksa *pmksa)
अणु
	पूर्णांक ret;
	trace_rdev_del_pmksa(&rdev->wiphy, netdev, pmksa);
	ret = rdev->ops->del_pmksa(&rdev->wiphy, netdev, pmksa);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_flush_pmksa(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   काष्ठा net_device *netdev)
अणु
	पूर्णांक ret;
	trace_rdev_flush_pmksa(&rdev->wiphy, netdev);
	ret = rdev->ops->flush_pmksa(&rdev->wiphy, netdev);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_reमुख्य_on_channel(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		       काष्ठा wireless_dev *wdev,
		       काष्ठा ieee80211_channel *chan,
		       अचिन्हित पूर्णांक duration, u64 *cookie)
अणु
	पूर्णांक ret;
	trace_rdev_reमुख्य_on_channel(&rdev->wiphy, wdev, chan, duration);
	ret = rdev->ops->reमुख्य_on_channel(&rdev->wiphy, wdev, chan,
					   duration, cookie);
	trace_rdev_वापस_पूर्णांक_cookie(&rdev->wiphy, ret, *cookie);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_cancel_reमुख्य_on_channel(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			      काष्ठा wireless_dev *wdev, u64 cookie)
अणु
	पूर्णांक ret;
	trace_rdev_cancel_reमुख्य_on_channel(&rdev->wiphy, wdev, cookie);
	ret = rdev->ops->cancel_reमुख्य_on_channel(&rdev->wiphy, wdev, cookie);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_mgmt_tx(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा wireless_dev *wdev,
			       काष्ठा cfg80211_mgmt_tx_params *params,
			       u64 *cookie)
अणु
	पूर्णांक ret;
	trace_rdev_mgmt_tx(&rdev->wiphy, wdev, params);
	ret = rdev->ops->mgmt_tx(&rdev->wiphy, wdev, params, cookie);
	trace_rdev_वापस_पूर्णांक_cookie(&rdev->wiphy, ret, *cookie);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_tx_control_port(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				       काष्ठा net_device *dev,
				       स्थिर व्योम *buf, माप_प्रकार len,
				       स्थिर u8 *dest, __be16 proto,
				       स्थिर bool noencrypt, u64 *cookie)
अणु
	पूर्णांक ret;
	trace_rdev_tx_control_port(&rdev->wiphy, dev, buf, len,
				   dest, proto, noencrypt);
	ret = rdev->ops->tx_control_port(&rdev->wiphy, dev, buf, len,
					 dest, proto, noencrypt, cookie);
	अगर (cookie)
		trace_rdev_वापस_पूर्णांक_cookie(&rdev->wiphy, ret, *cookie);
	अन्यथा
		trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_mgmt_tx_cancel_रुको(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा wireless_dev *wdev, u64 cookie)
अणु
	पूर्णांक ret;
	trace_rdev_mgmt_tx_cancel_रुको(&rdev->wiphy, wdev, cookie);
	ret = rdev->ops->mgmt_tx_cancel_रुको(&rdev->wiphy, wdev, cookie);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_set_घातer_mgmt(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				      काष्ठा net_device *dev, bool enabled,
				      पूर्णांक समयout)
अणु
	पूर्णांक ret;
	trace_rdev_set_घातer_mgmt(&rdev->wiphy, dev, enabled, समयout);
	ret = rdev->ops->set_घातer_mgmt(&rdev->wiphy, dev, enabled, समयout);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_cqm_rssi_config(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा net_device *dev, s32 rssi_thold, u32 rssi_hyst)
अणु
	पूर्णांक ret;
	trace_rdev_set_cqm_rssi_config(&rdev->wiphy, dev, rssi_thold,
				       rssi_hyst);
	ret = rdev->ops->set_cqm_rssi_config(&rdev->wiphy, dev, rssi_thold,
				       rssi_hyst);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_cqm_rssi_range_config(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा net_device *dev, s32 low, s32 high)
अणु
	पूर्णांक ret;
	trace_rdev_set_cqm_rssi_range_config(&rdev->wiphy, dev, low, high);
	ret = rdev->ops->set_cqm_rssi_range_config(&rdev->wiphy, dev,
						   low, high);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_cqm_txe_config(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			काष्ठा net_device *dev, u32 rate, u32 pkts, u32 पूर्णांकvl)
अणु
	पूर्णांक ret;
	trace_rdev_set_cqm_txe_config(&rdev->wiphy, dev, rate, pkts, पूर्णांकvl);
	ret = rdev->ops->set_cqm_txe_config(&rdev->wiphy, dev, rate, pkts,
					     पूर्णांकvl);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
rdev_update_mgmt_frame_registrations(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				     काष्ठा wireless_dev *wdev,
				     काष्ठा mgmt_frame_regs *upd)
अणु
	might_sleep();

	trace_rdev_update_mgmt_frame_registrations(&rdev->wiphy, wdev, upd);
	अगर (rdev->ops->update_mgmt_frame_registrations)
		rdev->ops->update_mgmt_frame_registrations(&rdev->wiphy, wdev,
							   upd);
	trace_rdev_वापस_व्योम(&rdev->wiphy);
पूर्ण

अटल अंतरभूत पूर्णांक rdev_set_antenna(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   u32 tx_ant, u32 rx_ant)
अणु
	पूर्णांक ret;
	trace_rdev_set_antenna(&rdev->wiphy, tx_ant, rx_ant);
	ret = rdev->ops->set_antenna(&rdev->wiphy, tx_ant, rx_ant);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_get_antenna(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   u32 *tx_ant, u32 *rx_ant)
अणु
	पूर्णांक ret;
	trace_rdev_get_antenna(&rdev->wiphy);
	ret = rdev->ops->get_antenna(&rdev->wiphy, tx_ant, rx_ant);
	अगर (ret)
		trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	अन्यथा
		trace_rdev_वापस_पूर्णांक_tx_rx(&rdev->wiphy, ret, *tx_ant,
					    *rx_ant);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_sched_scan_start(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		      काष्ठा net_device *dev,
		      काष्ठा cfg80211_sched_scan_request *request)
अणु
	पूर्णांक ret;
	trace_rdev_sched_scan_start(&rdev->wiphy, dev, request->reqid);
	ret = rdev->ops->sched_scan_start(&rdev->wiphy, dev, request);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_sched_scan_stop(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				       काष्ठा net_device *dev, u64 reqid)
अणु
	पूर्णांक ret;
	trace_rdev_sched_scan_stop(&rdev->wiphy, dev, reqid);
	ret = rdev->ops->sched_scan_stop(&rdev->wiphy, dev, reqid);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_set_rekey_data(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				      काष्ठा net_device *dev,
				      काष्ठा cfg80211_gtk_rekey_data *data)
अणु
	पूर्णांक ret;
	trace_rdev_set_rekey_data(&rdev->wiphy, dev);
	ret = rdev->ops->set_rekey_data(&rdev->wiphy, dev, data);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_tdls_mgmt(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा net_device *dev, u8 *peer,
				 u8 action_code, u8 dialog_token,
				 u16 status_code, u32 peer_capability,
				 bool initiator, स्थिर u8 *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;
	trace_rdev_tdls_mgmt(&rdev->wiphy, dev, peer, action_code,
			     dialog_token, status_code, peer_capability,
			     initiator, buf, len);
	ret = rdev->ops->tdls_mgmt(&rdev->wiphy, dev, peer, action_code,
				   dialog_token, status_code, peer_capability,
				   initiator, buf, len);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_tdls_oper(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा net_device *dev, u8 *peer,
				 क्रमागत nl80211_tdls_operation oper)
अणु
	पूर्णांक ret;
	trace_rdev_tdls_oper(&rdev->wiphy, dev, peer, oper);
	ret = rdev->ops->tdls_oper(&rdev->wiphy, dev, peer, oper);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_probe_client(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				    काष्ठा net_device *dev, स्थिर u8 *peer,
				    u64 *cookie)
अणु
	पूर्णांक ret;
	trace_rdev_probe_client(&rdev->wiphy, dev, peer);
	ret = rdev->ops->probe_client(&rdev->wiphy, dev, peer, cookie);
	trace_rdev_वापस_पूर्णांक_cookie(&rdev->wiphy, ret, *cookie);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_set_noack_map(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				     काष्ठा net_device *dev, u16 noack_map)
अणु
	पूर्णांक ret;
	trace_rdev_set_noack_map(&rdev->wiphy, dev, noack_map);
	ret = rdev->ops->set_noack_map(&rdev->wiphy, dev, noack_map);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_get_channel(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		 काष्ठा wireless_dev *wdev,
		 काष्ठा cfg80211_chan_def *chandef)
अणु
	पूर्णांक ret;

	trace_rdev_get_channel(&rdev->wiphy, wdev);
	ret = rdev->ops->get_channel(&rdev->wiphy, wdev, chandef);
	trace_rdev_वापस_chandef(&rdev->wiphy, ret, chandef);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_start_p2p_device(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
					काष्ठा wireless_dev *wdev)
अणु
	पूर्णांक ret;

	trace_rdev_start_p2p_device(&rdev->wiphy, wdev);
	ret = rdev->ops->start_p2p_device(&rdev->wiphy, wdev);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम rdev_stop_p2p_device(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
					काष्ठा wireless_dev *wdev)
अणु
	trace_rdev_stop_p2p_device(&rdev->wiphy, wdev);
	rdev->ops->stop_p2p_device(&rdev->wiphy, wdev);
	trace_rdev_वापस_व्योम(&rdev->wiphy);
पूर्ण

अटल अंतरभूत पूर्णांक rdev_start_nan(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा wireless_dev *wdev,
				 काष्ठा cfg80211_nan_conf *conf)
अणु
	पूर्णांक ret;

	trace_rdev_start_nan(&rdev->wiphy, wdev, conf);
	ret = rdev->ops->start_nan(&rdev->wiphy, wdev, conf);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम rdev_stop_nan(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा wireless_dev *wdev)
अणु
	trace_rdev_stop_nan(&rdev->wiphy, wdev);
	rdev->ops->stop_nan(&rdev->wiphy, wdev);
	trace_rdev_वापस_व्योम(&rdev->wiphy);
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_add_nan_func(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		  काष्ठा wireless_dev *wdev,
		  काष्ठा cfg80211_nan_func *nan_func)
अणु
	पूर्णांक ret;

	trace_rdev_add_nan_func(&rdev->wiphy, wdev, nan_func);
	ret = rdev->ops->add_nan_func(&rdev->wiphy, wdev, nan_func);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम rdev_del_nan_func(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				    काष्ठा wireless_dev *wdev, u64 cookie)
अणु
	trace_rdev_del_nan_func(&rdev->wiphy, wdev, cookie);
	rdev->ops->del_nan_func(&rdev->wiphy, wdev, cookie);
	trace_rdev_वापस_व्योम(&rdev->wiphy);
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_nan_change_conf(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		     काष्ठा wireless_dev *wdev,
		     काष्ठा cfg80211_nan_conf *conf, u32 changes)
अणु
	पूर्णांक ret;

	trace_rdev_nan_change_conf(&rdev->wiphy, wdev, conf, changes);
	अगर (rdev->ops->nan_change_conf)
		ret = rdev->ops->nan_change_conf(&rdev->wiphy, wdev, conf,
						 changes);
	अन्यथा
		ret = -ENOTSUPP;
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_set_mac_acl(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   काष्ठा net_device *dev,
				   काष्ठा cfg80211_acl_data *params)
अणु
	पूर्णांक ret;

	trace_rdev_set_mac_acl(&rdev->wiphy, dev, params);
	ret = rdev->ops->set_mac_acl(&rdev->wiphy, dev, params);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_update_ft_ies(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				     काष्ठा net_device *dev,
				     काष्ठा cfg80211_update_ft_ies_params *ftie)
अणु
	पूर्णांक ret;

	trace_rdev_update_ft_ies(&rdev->wiphy, dev, ftie);
	ret = rdev->ops->update_ft_ies(&rdev->wiphy, dev, ftie);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_crit_proto_start(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
					काष्ठा wireless_dev *wdev,
					क्रमागत nl80211_crit_proto_id protocol,
					u16 duration)
अणु
	पूर्णांक ret;

	trace_rdev_crit_proto_start(&rdev->wiphy, wdev, protocol, duration);
	ret = rdev->ops->crit_proto_start(&rdev->wiphy, wdev,
					  protocol, duration);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम rdev_crit_proto_stop(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				       काष्ठा wireless_dev *wdev)
अणु
	trace_rdev_crit_proto_stop(&rdev->wiphy, wdev);
	rdev->ops->crit_proto_stop(&rdev->wiphy, wdev);
	trace_rdev_वापस_व्योम(&rdev->wiphy);
पूर्ण

अटल अंतरभूत पूर्णांक rdev_channel_चयन(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				      काष्ठा net_device *dev,
				      काष्ठा cfg80211_csa_settings *params)
अणु
	पूर्णांक ret;

	trace_rdev_channel_चयन(&rdev->wiphy, dev, params);
	ret = rdev->ops->channel_चयन(&rdev->wiphy, dev, params);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_set_qos_map(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   काष्ठा net_device *dev,
				   काष्ठा cfg80211_qos_map *qos_map)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (rdev->ops->set_qos_map) अणु
		trace_rdev_set_qos_map(&rdev->wiphy, dev, qos_map);
		ret = rdev->ops->set_qos_map(&rdev->wiphy, dev, qos_map);
		trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_ap_chanwidth(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		      काष्ठा net_device *dev, काष्ठा cfg80211_chan_def *chandef)
अणु
	पूर्णांक ret;

	trace_rdev_set_ap_chanwidth(&rdev->wiphy, dev, chandef);
	ret = rdev->ops->set_ap_chanwidth(&rdev->wiphy, dev, chandef);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_add_tx_ts(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
	       काष्ठा net_device *dev, u8 tsid, स्थिर u8 *peer,
	       u8 user_prio, u16 admitted_समय)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	trace_rdev_add_tx_ts(&rdev->wiphy, dev, tsid, peer,
			     user_prio, admitted_समय);
	अगर (rdev->ops->add_tx_ts)
		ret = rdev->ops->add_tx_ts(&rdev->wiphy, dev, tsid, peer,
					   user_prio, admitted_समय);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_del_tx_ts(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
	       काष्ठा net_device *dev, u8 tsid, स्थिर u8 *peer)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	trace_rdev_del_tx_ts(&rdev->wiphy, dev, tsid, peer);
	अगर (rdev->ops->del_tx_ts)
		ret = rdev->ops->del_tx_ts(&rdev->wiphy, dev, tsid, peer);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_tdls_channel_चयन(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा net_device *dev, स्थिर u8 *addr,
			 u8 oper_class, काष्ठा cfg80211_chan_def *chandef)
अणु
	पूर्णांक ret;

	trace_rdev_tdls_channel_चयन(&rdev->wiphy, dev, addr, oper_class,
				       chandef);
	ret = rdev->ops->tdls_channel_चयन(&rdev->wiphy, dev, addr,
					     oper_class, chandef);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
rdev_tdls_cancel_channel_चयन(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				काष्ठा net_device *dev, स्थिर u8 *addr)
अणु
	trace_rdev_tdls_cancel_channel_चयन(&rdev->wiphy, dev, addr);
	rdev->ops->tdls_cancel_channel_चयन(&rdev->wiphy, dev, addr);
	trace_rdev_वापस_व्योम(&rdev->wiphy);
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_start_radar_detection(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			   काष्ठा net_device *dev,
			   काष्ठा cfg80211_chan_def *chandef,
			   u32 cac_समय_ms)
अणु
	पूर्णांक ret = -ENOTSUPP;

	trace_rdev_start_radar_detection(&rdev->wiphy, dev, chandef,
					 cac_समय_ms);
	अगर (rdev->ops->start_radar_detection)
		ret = rdev->ops->start_radar_detection(&rdev->wiphy, dev,
						       chandef, cac_समय_ms);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
rdev_end_cac(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
	     काष्ठा net_device *dev)
अणु
	trace_rdev_end_cac(&rdev->wiphy, dev);
	अगर (rdev->ops->end_cac)
		rdev->ops->end_cac(&rdev->wiphy, dev);
	trace_rdev_वापस_व्योम(&rdev->wiphy);
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_mcast_rate(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		    काष्ठा net_device *dev,
		    पूर्णांक mcast_rate[NUM_NL80211_BANDS])
अणु
	पूर्णांक ret = -ENOTSUPP;

	trace_rdev_set_mcast_rate(&rdev->wiphy, dev, mcast_rate);
	अगर (rdev->ops->set_mcast_rate)
		ret = rdev->ops->set_mcast_rate(&rdev->wiphy, dev, mcast_rate);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_coalesce(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		  काष्ठा cfg80211_coalesce *coalesce)
अणु
	पूर्णांक ret = -ENOTSUPP;

	trace_rdev_set_coalesce(&rdev->wiphy, coalesce);
	अगर (rdev->ops->set_coalesce)
		ret = rdev->ops->set_coalesce(&rdev->wiphy, coalesce);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_set_pmk(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा net_device *dev,
			       काष्ठा cfg80211_pmk_conf *pmk_conf)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	trace_rdev_set_pmk(&rdev->wiphy, dev, pmk_conf);
	अगर (rdev->ops->set_pmk)
		ret = rdev->ops->set_pmk(&rdev->wiphy, dev, pmk_conf);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_del_pmk(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा net_device *dev, स्थिर u8 *aa)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	trace_rdev_del_pmk(&rdev->wiphy, dev, aa);
	अगर (rdev->ops->del_pmk)
		ret = rdev->ops->del_pmk(&rdev->wiphy, dev, aa);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_बाह्यal_auth(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		   काष्ठा net_device *dev,
		   काष्ठा cfg80211_बाह्यal_auth_params *params)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	trace_rdev_बाह्यal_auth(&rdev->wiphy, dev, params);
	अगर (rdev->ops->बाह्यal_auth)
		ret = rdev->ops->बाह्यal_auth(&rdev->wiphy, dev, params);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_get_fपंचांग_responder_stats(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			     काष्ठा net_device *dev,
			     काष्ठा cfg80211_fपंचांग_responder_stats *fपंचांग_stats)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	trace_rdev_get_fपंचांग_responder_stats(&rdev->wiphy, dev, fपंचांग_stats);
	अगर (rdev->ops->get_fपंचांग_responder_stats)
		ret = rdev->ops->get_fपंचांग_responder_stats(&rdev->wiphy, dev,
							fपंचांग_stats);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_start_pmsr(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		काष्ठा wireless_dev *wdev,
		काष्ठा cfg80211_pmsr_request *request)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	trace_rdev_start_pmsr(&rdev->wiphy, wdev, request->cookie);
	अगर (rdev->ops->start_pmsr)
		ret = rdev->ops->start_pmsr(&rdev->wiphy, wdev, request);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
rdev_पात_pmsr(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		काष्ठा wireless_dev *wdev,
		काष्ठा cfg80211_pmsr_request *request)
अणु
	trace_rdev_पात_pmsr(&rdev->wiphy, wdev, request->cookie);
	अगर (rdev->ops->पात_pmsr)
		rdev->ops->पात_pmsr(&rdev->wiphy, wdev, request);
	trace_rdev_वापस_व्योम(&rdev->wiphy);
पूर्ण

अटल अंतरभूत पूर्णांक rdev_update_owe_info(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				       काष्ठा net_device *dev,
				       काष्ठा cfg80211_update_owe_info *oweinfo)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	trace_rdev_update_owe_info(&rdev->wiphy, dev, oweinfo);
	अगर (rdev->ops->update_owe_info)
		ret = rdev->ops->update_owe_info(&rdev->wiphy, dev, oweinfo);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_probe_mesh_link(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		     काष्ठा net_device *dev, स्थिर u8 *dest,
		     स्थिर व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;

	trace_rdev_probe_mesh_link(&rdev->wiphy, dev, dest, buf, len);
	ret = rdev->ops->probe_mesh_link(&rdev->wiphy, dev, buf, len);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_set_tid_config(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				      काष्ठा net_device *dev,
				      काष्ठा cfg80211_tid_config *tid_conf)
अणु
	पूर्णांक ret;

	trace_rdev_set_tid_config(&rdev->wiphy, dev, tid_conf);
	ret = rdev->ops->set_tid_config(&rdev->wiphy, dev, tid_conf);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_reset_tid_config(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
					काष्ठा net_device *dev, स्थिर u8 *peer,
					u8 tids)
अणु
	पूर्णांक ret;

	trace_rdev_reset_tid_config(&rdev->wiphy, dev, peer, tids);
	ret = rdev->ops->reset_tid_config(&rdev->wiphy, dev, peer, tids);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक rdev_set_sar_specs(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				     काष्ठा cfg80211_sar_specs *sar)
अणु
	पूर्णांक ret;

	trace_rdev_set_sar_specs(&rdev->wiphy, sar);
	ret = rdev->ops->set_sar_specs(&rdev->wiphy, sar);
	trace_rdev_वापस_पूर्णांक(&rdev->wiphy, ret);

	वापस ret;
पूर्ण

#पूर्ण_अगर /* __CFG80211_RDEV_OPS */
