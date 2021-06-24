<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010, Microsoft Corporation.
 *
 * Authors:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 *   Hank Janssen  <hjanssen@microsoft.com>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/reboot.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <घड़ीsource/hyperv_समयr.h>
#समावेश <यंत्र/mshyperv.h>

#समावेश "hyperv_vmbus.h"

#घोषणा SD_MAJOR	3
#घोषणा SD_MINOR	0
#घोषणा SD_MINOR_1	1
#घोषणा SD_MINOR_2	2
#घोषणा SD_VERSION_3_1	(SD_MAJOR << 16 | SD_MINOR_1)
#घोषणा SD_VERSION_3_2	(SD_MAJOR << 16 | SD_MINOR_2)
#घोषणा SD_VERSION	(SD_MAJOR << 16 | SD_MINOR)

#घोषणा SD_MAJOR_1	1
#घोषणा SD_VERSION_1	(SD_MAJOR_1 << 16 | SD_MINOR)

#घोषणा TS_MAJOR	4
#घोषणा TS_MINOR	0
#घोषणा TS_VERSION	(TS_MAJOR << 16 | TS_MINOR)

#घोषणा TS_MAJOR_1	1
#घोषणा TS_VERSION_1	(TS_MAJOR_1 << 16 | TS_MINOR)

#घोषणा TS_MAJOR_3	3
#घोषणा TS_VERSION_3	(TS_MAJOR_3 << 16 | TS_MINOR)

#घोषणा HB_MAJOR	3
#घोषणा HB_MINOR	0
#घोषणा HB_VERSION	(HB_MAJOR << 16 | HB_MINOR)

#घोषणा HB_MAJOR_1	1
#घोषणा HB_VERSION_1	(HB_MAJOR_1 << 16 | HB_MINOR)

अटल पूर्णांक sd_srv_version;
अटल पूर्णांक ts_srv_version;
अटल पूर्णांक hb_srv_version;

#घोषणा SD_VER_COUNT 4
अटल स्थिर पूर्णांक sd_versions[] = अणु
	SD_VERSION_3_2,
	SD_VERSION_3_1,
	SD_VERSION,
	SD_VERSION_1
पूर्ण;

#घोषणा TS_VER_COUNT 3
अटल स्थिर पूर्णांक ts_versions[] = अणु
	TS_VERSION,
	TS_VERSION_3,
	TS_VERSION_1
पूर्ण;

#घोषणा HB_VER_COUNT 2
अटल स्थिर पूर्णांक hb_versions[] = अणु
	HB_VERSION,
	HB_VERSION_1
पूर्ण;

#घोषणा FW_VER_COUNT 2
अटल स्थिर पूर्णांक fw_versions[] = अणु
	UTIL_FW_VERSION,
	UTIL_WS2K8_FW_VERSION
पूर्ण;

/*
 * Send the "hibernate" udev event in a thपढ़ो context.
 */
काष्ठा hibernate_work_context अणु
	काष्ठा work_काष्ठा work;
	काष्ठा hv_device *dev;
पूर्ण;

अटल काष्ठा hibernate_work_context hibernate_context;
अटल bool hibernation_supported;

अटल व्योम send_hibernate_uevent(काष्ठा work_काष्ठा *work)
अणु
	अक्षर *uevent_env[2] = अणु "EVENT=hibernate", शून्य पूर्ण;
	काष्ठा hibernate_work_context *ctx;

	ctx = container_of(work, काष्ठा hibernate_work_context, work);

	kobject_uevent_env(&ctx->dev->device.kobj, KOBJ_CHANGE, uevent_env);

	pr_info("Sent hibernation uevent\n");
पूर्ण

अटल पूर्णांक hv_shutकरोwn_init(काष्ठा hv_util_service *srv)
अणु
	काष्ठा vmbus_channel *channel = srv->channel;

	INIT_WORK(&hibernate_context.work, send_hibernate_uevent);
	hibernate_context.dev = channel->device_obj;

	hibernation_supported = hv_is_hibernation_supported();

	वापस 0;
पूर्ण

अटल व्योम shutकरोwn_onchannelcallback(व्योम *context);
अटल काष्ठा hv_util_service util_shutकरोwn = अणु
	.util_cb = shutकरोwn_onchannelcallback,
	.util_init = hv_shutकरोwn_init,
पूर्ण;

अटल पूर्णांक hv_बारync_init(काष्ठा hv_util_service *srv);
अटल पूर्णांक hv_बारync_pre_suspend(व्योम);
अटल व्योम hv_बारync_deinit(व्योम);

अटल व्योम बारync_onchannelcallback(व्योम *context);
अटल काष्ठा hv_util_service util_बारynch = अणु
	.util_cb = बारync_onchannelcallback,
	.util_init = hv_बारync_init,
	.util_pre_suspend = hv_बारync_pre_suspend,
	.util_deinit = hv_बारync_deinit,
पूर्ण;

अटल व्योम heartbeat_onchannelcallback(व्योम *context);
अटल काष्ठा hv_util_service util_heartbeat = अणु
	.util_cb = heartbeat_onchannelcallback,
पूर्ण;

अटल काष्ठा hv_util_service util_kvp = अणु
	.util_cb = hv_kvp_onchannelcallback,
	.util_init = hv_kvp_init,
	.util_pre_suspend = hv_kvp_pre_suspend,
	.util_pre_resume = hv_kvp_pre_resume,
	.util_deinit = hv_kvp_deinit,
पूर्ण;

अटल काष्ठा hv_util_service util_vss = अणु
	.util_cb = hv_vss_onchannelcallback,
	.util_init = hv_vss_init,
	.util_pre_suspend = hv_vss_pre_suspend,
	.util_pre_resume = hv_vss_pre_resume,
	.util_deinit = hv_vss_deinit,
पूर्ण;

अटल काष्ठा hv_util_service util_fcopy = अणु
	.util_cb = hv_fcopy_onchannelcallback,
	.util_init = hv_fcopy_init,
	.util_pre_suspend = hv_fcopy_pre_suspend,
	.util_pre_resume = hv_fcopy_pre_resume,
	.util_deinit = hv_fcopy_deinit,
पूर्ण;

अटल व्योम perक्रमm_shutकरोwn(काष्ठा work_काष्ठा *dummy)
अणु
	orderly_घातeroff(true);
पूर्ण

अटल व्योम perक्रमm_restart(काष्ठा work_काष्ठा *dummy)
अणु
	orderly_reboot();
पूर्ण

/*
 * Perक्रमm the shutकरोwn operation in a thपढ़ो context.
 */
अटल DECLARE_WORK(shutकरोwn_work, perक्रमm_shutकरोwn);

/*
 * Perक्रमm the restart operation in a thपढ़ो context.
 */
अटल DECLARE_WORK(restart_work, perक्रमm_restart);

अटल व्योम shutकरोwn_onchannelcallback(व्योम *context)
अणु
	काष्ठा vmbus_channel *channel = context;
	काष्ठा work_काष्ठा *work = शून्य;
	u32 recvlen;
	u64 requestid;
	u8  *shut_txf_buf = util_shutकरोwn.recv_buffer;

	काष्ठा shutकरोwn_msg_data *shutकरोwn_msg;

	काष्ठा icmsg_hdr *icmsghdrp;

	अगर (vmbus_recvpacket(channel, shut_txf_buf, HV_HYP_PAGE_SIZE, &recvlen, &requestid)) अणु
		pr_err_ratelimited("Shutdown request received. Could not read into shut txf buf\n");
		वापस;
	पूर्ण

	अगर (!recvlen)
		वापस;

	/* Ensure recvlen is big enough to पढ़ो header data */
	अगर (recvlen < ICMSG_HDR) अणु
		pr_err_ratelimited("Shutdown request received. Packet length too small: %d\n",
				   recvlen);
		वापस;
	पूर्ण

	icmsghdrp = (काष्ठा icmsg_hdr *)&shut_txf_buf[माप(काष्ठा vmbuspipe_hdr)];

	अगर (icmsghdrp->icmsgtype == ICMSGTYPE_NEGOTIATE) अणु
		अगर (vmbus_prep_negotiate_resp(icmsghdrp,
				shut_txf_buf, recvlen,
				fw_versions, FW_VER_COUNT,
				sd_versions, SD_VER_COUNT,
				शून्य, &sd_srv_version)) अणु
			pr_info("Shutdown IC version %d.%d\n",
				sd_srv_version >> 16,
				sd_srv_version & 0xFFFF);
		पूर्ण
	पूर्ण अन्यथा अगर (icmsghdrp->icmsgtype == ICMSGTYPE_SHUTDOWN) अणु
		/* Ensure recvlen is big enough to contain shutकरोwn_msg_data काष्ठा */
		अगर (recvlen < ICMSG_HDR + माप(काष्ठा shutकरोwn_msg_data)) अणु
			pr_err_ratelimited("Invalid shutdown msg data. Packet length too small: %u\n",
					   recvlen);
			वापस;
		पूर्ण

		shutकरोwn_msg = (काष्ठा shutकरोwn_msg_data *)&shut_txf_buf[ICMSG_HDR];

		/*
		 * shutकरोwn_msg->flags can be 0(shut करोwn), 2(reboot),
		 * or 4(hibernate). It may bitwise-OR 1, which means
		 * perक्रमming the request by क्रमce. Linux always tries
		 * to perक्रमm the request by क्रमce.
		 */
		चयन (shutकरोwn_msg->flags) अणु
		हाल 0:
		हाल 1:
			icmsghdrp->status = HV_S_OK;
			work = &shutकरोwn_work;
			pr_info("Shutdown request received - graceful shutdown initiated\n");
			अवरोध;
		हाल 2:
		हाल 3:
			icmsghdrp->status = HV_S_OK;
			work = &restart_work;
			pr_info("Restart request received - graceful restart initiated\n");
			अवरोध;
		हाल 4:
		हाल 5:
			pr_info("Hibernation request received\n");
			icmsghdrp->status = hibernation_supported ?
				HV_S_OK : HV_E_FAIL;
			अगर (hibernation_supported)
				work = &hibernate_context.work;
			अवरोध;
		शेष:
			icmsghdrp->status = HV_E_FAIL;
			pr_info("Shutdown request received - Invalid request\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		icmsghdrp->status = HV_E_FAIL;
		pr_err_ratelimited("Shutdown request received. Invalid msg type: %d\n",
				   icmsghdrp->icmsgtype);
	पूर्ण

	icmsghdrp->icflags = ICMSGHDRFLAG_TRANSACTION
		| ICMSGHDRFLAG_RESPONSE;

	vmbus_sendpacket(channel, shut_txf_buf,
			 recvlen, requestid,
			 VM_PKT_DATA_INBAND, 0);

	अगर (work)
		schedule_work(work);
पूर्ण

/*
 * Set the host समय in a process context.
 */
अटल काष्ठा work_काष्ठा adj_समय_work;

/*
 * The last समय sample, received from the host. PTP device responds to
 * requests by using this data and the current partition-wide समय reference
 * count.
 */
अटल काष्ठा अणु
	u64				host_समय;
	u64				ref_समय;
	spinlock_t			lock;
पूर्ण host_ts;

अटल अंतरभूत u64 refसमय_प्रकारo_ns(u64 refसमय)
अणु
	वापस (refसमय - WLTIMEDELTA) * 100;
पूर्ण

/*
 * Hard coded threshold क्रम host बारync delay: 600 seconds
 */
अटल स्थिर u64 HOST_TIMESYNC_DELAY_THRESH = 600 * (u64)NSEC_PER_SEC;

अटल पूर्णांक hv_get_adj_host_समय(काष्ठा बारpec64 *ts)
अणु
	u64 newसमय, refसमय, समयdअगरf_adj;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&host_ts.lock, flags);
	refसमय = hv_पढ़ो_reference_counter();

	/*
	 * We need to let the caller know that last update from host
	 * is older than the max allowable threshold. घड़ी_समय_लो()
	 * and PTP ioctl करो not have a करोcumented error that we could
	 * वापस क्रम this specअगरic हाल. Use ESTALE to report this.
	 */
	समयdअगरf_adj = refसमय - host_ts.ref_समय;
	अगर (समयdअगरf_adj * 100 > HOST_TIMESYNC_DELAY_THRESH) अणु
		pr_warn_once("TIMESYNC IC: Stale time stamp, %llu nsecs old\n",
			     (समयdअगरf_adj * 100));
		ret = -ESTALE;
	पूर्ण

	newसमय = host_ts.host_समय + समयdअगरf_adj;
	*ts = ns_to_बारpec64(refसमय_प्रकारo_ns(newसमय));
	spin_unlock_irqrestore(&host_ts.lock, flags);

	वापस ret;
पूर्ण

अटल व्योम hv_set_host_समय(काष्ठा work_काष्ठा *work)
अणु

	काष्ठा बारpec64 ts;

	अगर (!hv_get_adj_host_समय(&ts))
		करो_समय_रखोofday64(&ts);
पूर्ण

/*
 * Synchronize समय with host after reboot, restore, etc.
 *
 * ICTIMESYNCFLAG_SYNC flag bit indicates reboot, restore events of the VM.
 * After reboot the flag ICTIMESYNCFLAG_SYNC is included in the first समय
 * message after the बारync channel is खोलोed. Since the hv_utils module is
 * loaded after hv_vmbus, the first message is usually missed. This bit is
 * considered a hard request to discipline the घड़ी.
 *
 * ICTIMESYNCFLAG_SAMPLE bit indicates a समय sample from host. This is
 * typically used as a hपूर्णांक to the guest. The guest is under no obligation
 * to discipline the घड़ी.
 */
अटल अंतरभूत व्योम adj_guestसमय(u64 hostसमय, u64 refसमय, u8 adj_flags)
अणु
	अचिन्हित दीर्घ flags;
	u64 cur_refसमय;

	/*
	 * Save the adjusted समय sample from the host and the snapshot
	 * of the current प्रणाली समय.
	 */
	spin_lock_irqsave(&host_ts.lock, flags);

	cur_refसमय = hv_पढ़ो_reference_counter();
	host_ts.host_समय = hostसमय;
	host_ts.ref_समय = cur_refसमय;

	/*
	 * TimeSync v4 messages contain reference समय (guest's Hyper-V
	 * घड़ीsource पढ़ो when the समय sample was generated), we can
	 * improve the precision by adding the delta between now and the
	 * समय of generation. For older protocols we set
	 * refसमय == cur_refसमय on call.
	 */
	host_ts.host_समय += (cur_refसमय - refसमय);

	spin_unlock_irqrestore(&host_ts.lock, flags);

	/* Schedule work to करो करो_समय_रखोofday64() */
	अगर (adj_flags & ICTIMESYNCFLAG_SYNC)
		schedule_work(&adj_समय_work);
पूर्ण

/*
 * Time Sync Channel message handler.
 */
अटल व्योम बारync_onchannelcallback(व्योम *context)
अणु
	काष्ठा vmbus_channel *channel = context;
	u32 recvlen;
	u64 requestid;
	काष्ठा icmsg_hdr *icmsghdrp;
	काष्ठा iस_समयsync_data *समयdatap;
	काष्ठा iस_समयsync_ref_data *refdata;
	u8 *समय_प्रकारxf_buf = util_बारynch.recv_buffer;

	/*
	 * Drain the ring buffer and use the last packet to update
	 * host_ts
	 */
	जबतक (1) अणु
		पूर्णांक ret = vmbus_recvpacket(channel, समय_प्रकारxf_buf,
					   HV_HYP_PAGE_SIZE, &recvlen,
					   &requestid);
		अगर (ret) अणु
			pr_err_ratelimited("TimeSync IC pkt recv failed (Err: %d)\n",
					   ret);
			अवरोध;
		पूर्ण

		अगर (!recvlen)
			अवरोध;

		/* Ensure recvlen is big enough to पढ़ो header data */
		अगर (recvlen < ICMSG_HDR) अणु
			pr_err_ratelimited("Timesync request received. Packet length too small: %d\n",
					   recvlen);
			अवरोध;
		पूर्ण

		icmsghdrp = (काष्ठा icmsg_hdr *)&समय_प्रकारxf_buf[
				माप(काष्ठा vmbuspipe_hdr)];

		अगर (icmsghdrp->icmsgtype == ICMSGTYPE_NEGOTIATE) अणु
			अगर (vmbus_prep_negotiate_resp(icmsghdrp,
						समय_प्रकारxf_buf, recvlen,
						fw_versions, FW_VER_COUNT,
						ts_versions, TS_VER_COUNT,
						शून्य, &ts_srv_version)) अणु
				pr_info("TimeSync IC version %d.%d\n",
					ts_srv_version >> 16,
					ts_srv_version & 0xFFFF);
			पूर्ण
		पूर्ण अन्यथा अगर (icmsghdrp->icmsgtype == ICMSGTYPE_TIMESYNC) अणु
			अगर (ts_srv_version > TS_VERSION_3) अणु
				/* Ensure recvlen is big enough to पढ़ो iस_समयsync_ref_data */
				अगर (recvlen < ICMSG_HDR + माप(काष्ठा iस_समयsync_ref_data)) अणु
					pr_err_ratelimited("Invalid ictimesync ref data. Length too small: %u\n",
							   recvlen);
					अवरोध;
				पूर्ण
				refdata = (काष्ठा iस_समयsync_ref_data *)&समय_प्रकारxf_buf[ICMSG_HDR];

				adj_guestसमय(refdata->parentसमय,
						refdata->vmreferenceसमय,
						refdata->flags);
			पूर्ण अन्यथा अणु
				/* Ensure recvlen is big enough to पढ़ो iस_समयsync_data */
				अगर (recvlen < ICMSG_HDR + माप(काष्ठा iस_समयsync_data)) अणु
					pr_err_ratelimited("Invalid ictimesync data. Length too small: %u\n",
							   recvlen);
					अवरोध;
				पूर्ण
				समयdatap = (काष्ठा iस_समयsync_data *)&समय_प्रकारxf_buf[ICMSG_HDR];

				adj_guestसमय(समयdatap->parentसमय,
					      hv_पढ़ो_reference_counter(),
					      समयdatap->flags);
			पूर्ण
		पूर्ण अन्यथा अणु
			icmsghdrp->status = HV_E_FAIL;
			pr_err_ratelimited("Timesync request received. Invalid msg type: %d\n",
					   icmsghdrp->icmsgtype);
		पूर्ण

		icmsghdrp->icflags = ICMSGHDRFLAG_TRANSACTION
			| ICMSGHDRFLAG_RESPONSE;

		vmbus_sendpacket(channel, समय_प्रकारxf_buf,
				 recvlen, requestid,
				 VM_PKT_DATA_INBAND, 0);
	पूर्ण
पूर्ण

/*
 * Heartbeat functionality.
 * Every two seconds, Hyper-V send us a heartbeat request message.
 * we respond to this message, and Hyper-V knows we are alive.
 */
अटल व्योम heartbeat_onchannelcallback(व्योम *context)
अणु
	काष्ठा vmbus_channel *channel = context;
	u32 recvlen;
	u64 requestid;
	काष्ठा icmsg_hdr *icmsghdrp;
	काष्ठा heartbeat_msg_data *heartbeat_msg;
	u8 *hbeat_txf_buf = util_heartbeat.recv_buffer;

	जबतक (1) अणु

		अगर (vmbus_recvpacket(channel, hbeat_txf_buf, HV_HYP_PAGE_SIZE,
				     &recvlen, &requestid)) अणु
			pr_err_ratelimited("Heartbeat request received. Could not read into hbeat txf buf\n");
			वापस;
		पूर्ण

		अगर (!recvlen)
			अवरोध;

		/* Ensure recvlen is big enough to पढ़ो header data */
		अगर (recvlen < ICMSG_HDR) अणु
			pr_err_ratelimited("Heartbeat request received. Packet length too small: %d\n",
					   recvlen);
			अवरोध;
		पूर्ण

		icmsghdrp = (काष्ठा icmsg_hdr *)&hbeat_txf_buf[
				माप(काष्ठा vmbuspipe_hdr)];

		अगर (icmsghdrp->icmsgtype == ICMSGTYPE_NEGOTIATE) अणु
			अगर (vmbus_prep_negotiate_resp(icmsghdrp,
					hbeat_txf_buf, recvlen,
					fw_versions, FW_VER_COUNT,
					hb_versions, HB_VER_COUNT,
					शून्य, &hb_srv_version)) अणु

				pr_info("Heartbeat IC version %d.%d\n",
					hb_srv_version >> 16,
					hb_srv_version & 0xFFFF);
			पूर्ण
		पूर्ण अन्यथा अगर (icmsghdrp->icmsgtype == ICMSGTYPE_HEARTBEAT) अणु
			/*
			 * Ensure recvlen is big enough to पढ़ो seq_num. Reserved area is not
			 * included in the check as the host may not fill it up entirely
			 */
			अगर (recvlen < ICMSG_HDR + माप(u64)) अणु
				pr_err_ratelimited("Invalid heartbeat msg data. Length too small: %u\n",
						   recvlen);
				अवरोध;
			पूर्ण
			heartbeat_msg = (काष्ठा heartbeat_msg_data *)&hbeat_txf_buf[ICMSG_HDR];

			heartbeat_msg->seq_num += 1;
		पूर्ण अन्यथा अणु
			icmsghdrp->status = HV_E_FAIL;
			pr_err_ratelimited("Heartbeat request received. Invalid msg type: %d\n",
					   icmsghdrp->icmsgtype);
		पूर्ण

		icmsghdrp->icflags = ICMSGHDRFLAG_TRANSACTION
			| ICMSGHDRFLAG_RESPONSE;

		vmbus_sendpacket(channel, hbeat_txf_buf,
				 recvlen, requestid,
				 VM_PKT_DATA_INBAND, 0);
	पूर्ण
पूर्ण

#घोषणा HV_UTIL_RING_SEND_SIZE VMBUS_RING_SIZE(3 * HV_HYP_PAGE_SIZE)
#घोषणा HV_UTIL_RING_RECV_SIZE VMBUS_RING_SIZE(3 * HV_HYP_PAGE_SIZE)

अटल पूर्णांक util_probe(काष्ठा hv_device *dev,
			स्थिर काष्ठा hv_vmbus_device_id *dev_id)
अणु
	काष्ठा hv_util_service *srv =
		(काष्ठा hv_util_service *)dev_id->driver_data;
	पूर्णांक ret;

	srv->recv_buffer = kदो_स्मृति(HV_HYP_PAGE_SIZE * 4, GFP_KERNEL);
	अगर (!srv->recv_buffer)
		वापस -ENOMEM;
	srv->channel = dev->channel;
	अगर (srv->util_init) अणु
		ret = srv->util_init(srv);
		अगर (ret) अणु
			ret = -ENODEV;
			जाओ error1;
		पूर्ण
	पूर्ण

	/*
	 * The set of services managed by the util driver are not perक्रमmance
	 * critical and करो not need batched पढ़ोing. Furthermore, some services
	 * such as KVP can only handle one message from the host at a समय.
	 * Turn off batched पढ़ोing क्रम all util drivers beक्रमe we खोलो the
	 * channel.
	 */
	set_channel_पढ़ो_mode(dev->channel, HV_CALL_सूचीECT);

	hv_set_drvdata(dev, srv);

	ret = vmbus_खोलो(dev->channel, HV_UTIL_RING_SEND_SIZE,
			 HV_UTIL_RING_RECV_SIZE, शून्य, 0, srv->util_cb,
			 dev->channel);
	अगर (ret)
		जाओ error;

	वापस 0;

error:
	अगर (srv->util_deinit)
		srv->util_deinit();
error1:
	kमुक्त(srv->recv_buffer);
	वापस ret;
पूर्ण

अटल पूर्णांक util_हटाओ(काष्ठा hv_device *dev)
अणु
	काष्ठा hv_util_service *srv = hv_get_drvdata(dev);

	अगर (srv->util_deinit)
		srv->util_deinit();
	vmbus_बंद(dev->channel);
	kमुक्त(srv->recv_buffer);

	वापस 0;
पूर्ण

/*
 * When we're in util_suspend(), all the userspace processes have been frozen
 * (refer to hibernate() -> मुक्तze_processes()). The userspace is thawed only
 * after the whole resume procedure, including util_resume(), finishes.
 */
अटल पूर्णांक util_suspend(काष्ठा hv_device *dev)
अणु
	काष्ठा hv_util_service *srv = hv_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (srv->util_pre_suspend) अणु
		ret = srv->util_pre_suspend();
		अगर (ret)
			वापस ret;
	पूर्ण

	vmbus_बंद(dev->channel);

	वापस 0;
पूर्ण

अटल पूर्णांक util_resume(काष्ठा hv_device *dev)
अणु
	काष्ठा hv_util_service *srv = hv_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (srv->util_pre_resume) अणु
		ret = srv->util_pre_resume();
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = vmbus_खोलो(dev->channel, HV_UTIL_RING_SEND_SIZE,
			 HV_UTIL_RING_RECV_SIZE, शून्य, 0, srv->util_cb,
			 dev->channel);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hv_vmbus_device_id id_table[] = अणु
	/* Shutकरोwn guid */
	अणु HV_SHUTDOWN_GUID,
	  .driver_data = (अचिन्हित दीर्घ)&util_shutकरोwn
	पूर्ण,
	/* Time synch guid */
	अणु HV_TS_GUID,
	  .driver_data = (अचिन्हित दीर्घ)&util_बारynch
	पूर्ण,
	/* Heartbeat guid */
	अणु HV_HEART_BEAT_GUID,
	  .driver_data = (अचिन्हित दीर्घ)&util_heartbeat
	पूर्ण,
	/* KVP guid */
	अणु HV_KVP_GUID,
	  .driver_data = (अचिन्हित दीर्घ)&util_kvp
	पूर्ण,
	/* VSS GUID */
	अणु HV_VSS_GUID,
	  .driver_data = (अचिन्हित दीर्घ)&util_vss
	पूर्ण,
	/* File copy GUID */
	अणु HV_FCOPY_GUID,
	  .driver_data = (अचिन्हित दीर्घ)&util_fcopy
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(vmbus, id_table);

/* The one and only one */
अटल  काष्ठा hv_driver util_drv = अणु
	.name = "hv_utils",
	.id_table = id_table,
	.probe =  util_probe,
	.हटाओ =  util_हटाओ,
	.suspend = util_suspend,
	.resume =  util_resume,
	.driver = अणु
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक hv_ptp_enable(काष्ठा ptp_घड़ी_info *info,
			 काष्ठा ptp_घड़ी_request *request, पूर्णांक on)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक hv_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *p, स्थिर काष्ठा बारpec64 *ts)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक hv_ptp_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 delta)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल पूर्णांक hv_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक hv_ptp_समय_लो(काष्ठा ptp_घड़ी_info *info, काष्ठा बारpec64 *ts)
अणु
	वापस hv_get_adj_host_समय(ts);
पूर्ण

अटल काष्ठा ptp_घड़ी_info ptp_hyperv_info = अणु
	.name		= "hyperv",
	.enable         = hv_ptp_enable,
	.adjसमय        = hv_ptp_adjसमय,
	.adjfreq        = hv_ptp_adjfreq,
	.समय_लो64      = hv_ptp_समय_लो,
	.समय_रखो64      = hv_ptp_समय_रखो,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा ptp_घड़ी *hv_ptp_घड़ी;

अटल पूर्णांक hv_बारync_init(काष्ठा hv_util_service *srv)
अणु
	/* TimeSync requires Hyper-V घड़ीsource. */
	अगर (!hv_पढ़ो_reference_counter)
		वापस -ENODEV;

	spin_lock_init(&host_ts.lock);

	INIT_WORK(&adj_समय_work, hv_set_host_समय);

	/*
	 * ptp_घड़ी_रेजिस्टर() वापसs शून्य when CONFIG_PTP_1588_CLOCK is
	 * disabled but the driver is still useful without the PTP device
	 * as it still handles the ICTIMESYNCFLAG_SYNC हाल.
	 */
	hv_ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&ptp_hyperv_info, शून्य);
	अगर (IS_ERR_OR_शून्य(hv_ptp_घड़ी)) अणु
		pr_err("cannot register PTP clock: %ld\n",
		       PTR_ERR(hv_ptp_घड़ी));
		hv_ptp_घड़ी = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hv_बारync_cancel_work(व्योम)
अणु
	cancel_work_sync(&adj_समय_work);
पूर्ण

अटल पूर्णांक hv_बारync_pre_suspend(व्योम)
अणु
	hv_बारync_cancel_work();
	वापस 0;
पूर्ण

अटल व्योम hv_बारync_deinit(व्योम)
अणु
	अगर (hv_ptp_घड़ी)
		ptp_घड़ी_unरेजिस्टर(hv_ptp_घड़ी);

	hv_बारync_cancel_work();
पूर्ण

अटल पूर्णांक __init init_hyperv_utils(व्योम)
अणु
	pr_info("Registering HyperV Utility Driver\n");

	वापस vmbus_driver_रेजिस्टर(&util_drv);
पूर्ण

अटल व्योम निकास_hyperv_utils(व्योम)
अणु
	pr_info("De-Registered HyperV Utility Driver\n");

	vmbus_driver_unरेजिस्टर(&util_drv);
पूर्ण

module_init(init_hyperv_utils);
module_निकास(निकास_hyperv_utils);

MODULE_DESCRIPTION("Hyper-V Utilities");
MODULE_LICENSE("GPL");
