<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ieee80211.h>
#समावेश <linux/export.h>
#समावेश <net/cfg80211.h>
#समावेश "nl80211.h"
#समावेश "core.h"
#समावेश "rdev-ops.h"

/* Default values, समयouts in ms */
#घोषणा MESH_TTL 		31
#घोषणा MESH_DEFAULT_ELEMENT_TTL 31
#घोषणा MESH_MAX_RETR	 	3
#घोषणा MESH_RET_T 		100
#घोषणा MESH_CONF_T 		100
#घोषणा MESH_HOLD_T 		100

#घोषणा MESH_PATH_TIMEOUT	5000
#घोषणा MESH_RANN_INTERVAL      5000
#घोषणा MESH_PATH_TO_ROOT_TIMEOUT      6000
#घोषणा MESH_ROOT_INTERVAL     5000
#घोषणा MESH_ROOT_CONFIRMATION_INTERVAL 2000
#घोषणा MESH_DEFAULT_PLINK_TIMEOUT	1800 /* समयout in seconds */

/*
 * Minimum पूर्णांकerval between two consecutive PREQs originated by the same
 * पूर्णांकerface
 */
#घोषणा MESH_PREQ_MIN_INT	10
#घोषणा MESH_PERR_MIN_INT	100
#घोषणा MESH_DIAM_TRAVERSAL_TIME 50

#घोषणा MESH_RSSI_THRESHOLD	0

/*
 * A path will be refreshed अगर it is used PATH_REFRESH_TIME milliseconds
 * beक्रमe timing out.  This way it will reमुख्य ACTIVE and no data frames
 * will be unnecessarily held in the pending queue.
 */
#घोषणा MESH_PATH_REFRESH_TIME			1000
#घोषणा MESH_MIN_DISCOVERY_TIMEOUT (2 * MESH_DIAM_TRAVERSAL_TIME)

/* Default maximum number of established plinks per पूर्णांकerface */
#घोषणा MESH_MAX_ESTAB_PLINKS	32

#घोषणा MESH_MAX_PREQ_RETRIES	4

#घोषणा MESH_SYNC_NEIGHBOR_OFFSET_MAX 50

#घोषणा MESH_DEFAULT_BEACON_INTERVAL	1000	/* in 1024 us units (=TUs) */
#घोषणा MESH_DEFAULT_DTIM_PERIOD	2
#घोषणा MESH_DEFAULT_AWAKE_WINDOW	10	/* in 1024 us units (=TUs) */

स्थिर काष्ठा mesh_config शेष_mesh_config = अणु
	.करोt11MeshRetryTimeout = MESH_RET_T,
	.करोt11MeshConfirmTimeout = MESH_CONF_T,
	.करोt11MeshHoldingTimeout = MESH_HOLD_T,
	.करोt11MeshMaxRetries = MESH_MAX_RETR,
	.करोt11MeshTTL = MESH_TTL,
	.element_ttl = MESH_DEFAULT_ELEMENT_TTL,
	.स्वतः_खोलो_plinks = true,
	.करोt11MeshMaxPeerLinks = MESH_MAX_ESTAB_PLINKS,
	.करोt11MeshNbrOffsetMaxNeighbor = MESH_SYNC_NEIGHBOR_OFFSET_MAX,
	.करोt11MeshHWMPactivePathTimeout = MESH_PATH_TIMEOUT,
	.करोt11MeshHWMPpreqMinInterval = MESH_PREQ_MIN_INT,
	.करोt11MeshHWMPperrMinInterval = MESH_PERR_MIN_INT,
	.करोt11MeshHWMPnetDiameterTraversalTime = MESH_DIAM_TRAVERSAL_TIME,
	.करोt11MeshHWMPmaxPREQretries = MESH_MAX_PREQ_RETRIES,
	.path_refresh_समय = MESH_PATH_REFRESH_TIME,
	.min_discovery_समयout = MESH_MIN_DISCOVERY_TIMEOUT,
	.करोt11MeshHWMPRannInterval = MESH_RANN_INTERVAL,
	.करोt11MeshGateAnnouncementProtocol = false,
	.करोt11MeshForwarding = true,
	.rssi_threshold = MESH_RSSI_THRESHOLD,
	.ht_opmode = IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED,
	.करोt11MeshHWMPactivePathToRootTimeout = MESH_PATH_TO_ROOT_TIMEOUT,
	.करोt11MeshHWMProotInterval = MESH_ROOT_INTERVAL,
	.करोt11MeshHWMPconfirmationInterval = MESH_ROOT_CONFIRMATION_INTERVAL,
	.घातer_mode = NL80211_MESH_POWER_ACTIVE,
	.करोt11MeshAwakeWinकरोwDuration = MESH_DEFAULT_AWAKE_WINDOW,
	.plink_समयout = MESH_DEFAULT_PLINK_TIMEOUT,
	.करोt11MeshNolearn = false,
पूर्ण;

स्थिर काष्ठा mesh_setup शेष_mesh_setup = अणु
	/* cfg80211_join_mesh() will pick a channel अगर needed */
	.sync_method = IEEE80211_SYNC_METHOD_NEIGHBOR_OFFSET,
	.path_sel_proto = IEEE80211_PATH_PROTOCOL_HWMP,
	.path_metric = IEEE80211_PATH_METRIC_AIRTIME,
	.auth_id = 0, /* खोलो */
	.ie = शून्य,
	.ie_len = 0,
	.is_secure = false,
	.user_mpm = false,
	.beacon_पूर्णांकerval = MESH_DEFAULT_BEACON_INTERVAL,
	.dtim_period = MESH_DEFAULT_DTIM_PERIOD,
पूर्ण;

पूर्णांक __cfg80211_join_mesh(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा net_device *dev,
			 काष्ठा mesh_setup *setup,
			 स्थिर काष्ठा mesh_config *conf)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err;

	BUILD_BUG_ON(IEEE80211_MAX_SSID_LEN != IEEE80211_MAX_MESH_ID_LEN);

	ASSERT_WDEV_LOCK(wdev);

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_MESH_POINT)
		वापस -EOPNOTSUPP;

	अगर (!(rdev->wiphy.flags & WIPHY_FLAG_MESH_AUTH) &&
	      setup->is_secure)
		वापस -EOPNOTSUPP;

	अगर (wdev->mesh_id_len)
		वापस -EALREADY;

	अगर (!setup->mesh_id_len)
		वापस -EINVAL;

	अगर (!rdev->ops->join_mesh)
		वापस -EOPNOTSUPP;

	अगर (!setup->chandef.chan) अणु
		/* अगर no channel explicitly given, use preset channel */
		setup->chandef = wdev->preset_chandef;
	पूर्ण

	अगर (!setup->chandef.chan) अणु
		/* अगर we करोn't have that either, use the first usable channel */
		क्रमागत nl80211_band band;

		क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
			काष्ठा ieee80211_supported_band *sband;
			काष्ठा ieee80211_channel *chan;
			पूर्णांक i;

			sband = rdev->wiphy.bands[band];
			अगर (!sband)
				जारी;

			क्रम (i = 0; i < sband->n_channels; i++) अणु
				chan = &sband->channels[i];
				अगर (chan->flags & (IEEE80211_CHAN_NO_IR |
						   IEEE80211_CHAN_DISABLED |
						   IEEE80211_CHAN_RADAR))
					जारी;
				setup->chandef.chan = chan;
				अवरोध;
			पूर्ण

			अगर (setup->chandef.chan)
				अवरोध;
		पूर्ण

		/* no usable channel ... */
		अगर (!setup->chandef.chan)
			वापस -EINVAL;

		setup->chandef.width = NL80211_CHAN_WIDTH_20_NOHT;
		setup->chandef.center_freq1 = setup->chandef.chan->center_freq;
	पूर्ण

	/*
	 * check अगर basic rates are available otherwise use mandatory rates as
	 * basic rates
	 */
	अगर (!setup->basic_rates) अणु
		क्रमागत nl80211_bss_scan_width scan_width;
		काष्ठा ieee80211_supported_band *sband =
				rdev->wiphy.bands[setup->chandef.chan->band];

		अगर (setup->chandef.chan->band == NL80211_BAND_2GHZ) अणु
			पूर्णांक i;

			/*
			 * Older versions selected the mandatory rates क्रम
			 * 2.4 GHz as well, but were broken in that only
			 * 1 Mbps was regarded as a mandatory rate. Keep
			 * using just 1 Mbps as the शेष basic rate क्रम
			 * mesh to be पूर्णांकeroperable with older versions.
			 */
			क्रम (i = 0; i < sband->n_bitrates; i++) अणु
				अगर (sband->bitrates[i].bitrate == 10) अणु
					setup->basic_rates = BIT(i);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			scan_width = cfg80211_chandef_to_scan_width(&setup->chandef);
			setup->basic_rates = ieee80211_mandatory_rates(sband,
								       scan_width);
		पूर्ण
	पूर्ण

	err = cfg80211_chandef_dfs_required(&rdev->wiphy,
					    &setup->chandef,
					    NL80211_IFTYPE_MESH_POINT);
	अगर (err < 0)
		वापस err;
	अगर (err > 0 && !setup->userspace_handles_dfs)
		वापस -EINVAL;

	अगर (!cfg80211_reg_can_beacon(&rdev->wiphy, &setup->chandef,
				     NL80211_IFTYPE_MESH_POINT))
		वापस -EINVAL;

	err = rdev_join_mesh(rdev, dev, conf, setup);
	अगर (!err) अणु
		स_नकल(wdev->ssid, setup->mesh_id, setup->mesh_id_len);
		wdev->mesh_id_len = setup->mesh_id_len;
		wdev->chandef = setup->chandef;
		wdev->beacon_पूर्णांकerval = setup->beacon_पूर्णांकerval;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक cfg80211_set_mesh_channel(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			      काष्ठा wireless_dev *wdev,
			      काष्ठा cfg80211_chan_def *chandef)
अणु
	पूर्णांक err;

	/*
	 * Workaround क्रम libertas (only!), it माला_दो the पूर्णांकerface
	 * पूर्णांकo mesh mode but करोesn't implement join_mesh. Instead,
	 * it is configured via sysfs and then joins the mesh when
	 * you set the channel. Note that the libertas mesh isn't
	 * compatible with 802.11 mesh.
	 */
	अगर (rdev->ops->libertas_set_mesh_channel) अणु
		अगर (chandef->width != NL80211_CHAN_WIDTH_20_NOHT)
			वापस -EINVAL;

		अगर (!netअगर_running(wdev->netdev))
			वापस -ENETDOWN;

		err = rdev_libertas_set_mesh_channel(rdev, wdev->netdev,
						     chandef->chan);
		अगर (!err)
			wdev->chandef = *chandef;

		वापस err;
	पूर्ण

	अगर (wdev->mesh_id_len)
		वापस -EBUSY;

	wdev->preset_chandef = *chandef;
	वापस 0;
पूर्ण

पूर्णांक __cfg80211_leave_mesh(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा net_device *dev)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err;

	ASSERT_WDEV_LOCK(wdev);

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_MESH_POINT)
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->leave_mesh)
		वापस -EOPNOTSUPP;

	अगर (!wdev->mesh_id_len)
		वापस -ENOTCONN;

	err = rdev_leave_mesh(rdev, dev);
	अगर (!err) अणु
		wdev->conn_owner_nlportid = 0;
		wdev->mesh_id_len = 0;
		wdev->beacon_पूर्णांकerval = 0;
		स_रखो(&wdev->chandef, 0, माप(wdev->chandef));
		rdev_set_qos_map(rdev, dev, शून्य);
		cfg80211_sched_dfs_chan_update(rdev);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक cfg80211_leave_mesh(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			काष्ठा net_device *dev)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err;

	wdev_lock(wdev);
	err = __cfg80211_leave_mesh(rdev, dev);
	wdev_unlock(wdev);

	वापस err;
पूर्ण
