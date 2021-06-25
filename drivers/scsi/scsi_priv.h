<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SCSI_PRIV_H
#घोषणा _SCSI_PRIV_H

#समावेश <linux/device.h>
#समावेश <linux/async.h>
#समावेश <scsi/scsi_device.h>
#समावेश <linux/sbiपंचांगap.h>

काष्ठा request_queue;
काष्ठा request;
काष्ठा scsi_cmnd;
काष्ठा scsi_device;
काष्ठा scsi_target;
काष्ठा scsi_host_ढाँचा;
काष्ठा Scsi_Host;
काष्ठा scsi_nl_hdr;

#घोषणा SCSI_CMD_RETRIES_NO_LIMIT -1

/*
 * Scsi Error Handler Flags
 */
#घोषणा SCSI_EH_ABORT_SCHEDULED	0x0002	/* Abort has been scheduled */

#घोषणा SCSI_SENSE_VALID(scmd) \
	(((scmd)->sense_buffer[0] & 0x70) == 0x70)

/* hosts.c */
बाह्य पूर्णांक scsi_init_hosts(व्योम);
बाह्य व्योम scsi_निकास_hosts(व्योम);

/* scsi.c */
पूर्णांक scsi_init_sense_cache(काष्ठा Scsi_Host *shost);
व्योम scsi_init_command(काष्ठा scsi_device *dev, काष्ठा scsi_cmnd *cmd);
#अगर_घोषित CONFIG_SCSI_LOGGING
व्योम scsi_log_send(काष्ठा scsi_cmnd *cmd);
व्योम scsi_log_completion(काष्ठा scsi_cmnd *cmd, पूर्णांक disposition);
#अन्यथा
अटल अंतरभूत व्योम scsi_log_send(काष्ठा scsi_cmnd *cmd) 
	अणु पूर्ण;
अटल अंतरभूत व्योम scsi_log_completion(काष्ठा scsi_cmnd *cmd, पूर्णांक disposition)
	अणु पूर्ण;
#पूर्ण_अगर

/* scsi_devinfo.c */

/* list of keys क्रम the lists */
क्रमागत scsi_devinfo_key अणु
	SCSI_DEVINFO_GLOBAL = 0,
	SCSI_DEVINFO_SPI,
पूर्ण;

बाह्य blist_flags_t scsi_get_device_flags(काष्ठा scsi_device *sdev,
					   स्थिर अचिन्हित अक्षर *venकरोr,
					   स्थिर अचिन्हित अक्षर *model);
बाह्य blist_flags_t scsi_get_device_flags_keyed(काष्ठा scsi_device *sdev,
						 स्थिर अचिन्हित अक्षर *venकरोr,
						 स्थिर अचिन्हित अक्षर *model,
						 क्रमागत scsi_devinfo_key key);
बाह्य पूर्णांक scsi_dev_info_list_add_keyed(पूर्णांक compatible, अक्षर *venकरोr,
					अक्षर *model, अक्षर *strflags,
					blist_flags_t flags,
					क्रमागत scsi_devinfo_key key);
बाह्य पूर्णांक scsi_dev_info_list_del_keyed(अक्षर *venकरोr, अक्षर *model,
					क्रमागत scsi_devinfo_key key);
बाह्य पूर्णांक scsi_dev_info_add_list(क्रमागत scsi_devinfo_key key, स्थिर अक्षर *name);
बाह्य पूर्णांक scsi_dev_info_हटाओ_list(क्रमागत scsi_devinfo_key key);

बाह्य पूर्णांक __init scsi_init_devinfo(व्योम);
बाह्य व्योम scsi_निकास_devinfo(व्योम);

/* scsi_error.c */
बाह्य व्योम scmd_eh_पात_handler(काष्ठा work_काष्ठा *work);
बाह्य क्रमागत blk_eh_समयr_वापस scsi_बार_out(काष्ठा request *req);
बाह्य पूर्णांक scsi_error_handler(व्योम *host);
बाह्य क्रमागत scsi_disposition scsi_decide_disposition(काष्ठा scsi_cmnd *cmd);
बाह्य व्योम scsi_eh_wakeup(काष्ठा Scsi_Host *shost);
बाह्य व्योम scsi_eh_scmd_add(काष्ठा scsi_cmnd *);
व्योम scsi_eh_पढ़ोy_devs(काष्ठा Scsi_Host *shost,
			काष्ठा list_head *work_q,
			काष्ठा list_head *करोne_q);
पूर्णांक scsi_eh_get_sense(काष्ठा list_head *work_q,
		      काष्ठा list_head *करोne_q);
पूर्णांक scsi_noretry_cmd(काष्ठा scsi_cmnd *scmd);

/* scsi_lib.c */
बाह्य पूर्णांक scsi_maybe_unblock_host(काष्ठा scsi_device *sdev);
बाह्य व्योम scsi_device_unbusy(काष्ठा scsi_device *sdev, काष्ठा scsi_cmnd *cmd);
बाह्य व्योम scsi_queue_insert(काष्ठा scsi_cmnd *cmd, पूर्णांक reason);
बाह्य व्योम scsi_io_completion(काष्ठा scsi_cmnd *, अचिन्हित पूर्णांक);
बाह्य व्योम scsi_run_host_queues(काष्ठा Scsi_Host *shost);
बाह्य व्योम scsi_requeue_run_queue(काष्ठा work_काष्ठा *work);
बाह्य काष्ठा request_queue *scsi_mq_alloc_queue(काष्ठा scsi_device *sdev);
बाह्य व्योम scsi_start_queue(काष्ठा scsi_device *sdev);
बाह्य पूर्णांक scsi_mq_setup_tags(काष्ठा Scsi_Host *shost);
बाह्य व्योम scsi_mq_destroy_tags(काष्ठा Scsi_Host *shost);
बाह्य व्योम scsi_निकास_queue(व्योम);
बाह्य व्योम scsi_evt_thपढ़ो(काष्ठा work_काष्ठा *work);

/* scsi_proc.c */
#अगर_घोषित CONFIG_SCSI_PROC_FS
बाह्य व्योम scsi_proc_hostdir_add(काष्ठा scsi_host_ढाँचा *);
बाह्य व्योम scsi_proc_hostdir_rm(काष्ठा scsi_host_ढाँचा *);
बाह्य व्योम scsi_proc_host_add(काष्ठा Scsi_Host *);
बाह्य व्योम scsi_proc_host_rm(काष्ठा Scsi_Host *);
बाह्य पूर्णांक scsi_init_procfs(व्योम);
बाह्य व्योम scsi_निकास_procfs(व्योम);
#अन्यथा
# define scsi_proc_hostdir_add(sht)	करो अणु पूर्ण जबतक (0)
# define scsi_proc_hostdir_rm(sht)	करो अणु पूर्ण जबतक (0)
# define scsi_proc_host_add(shost)	करो अणु पूर्ण जबतक (0)
# define scsi_proc_host_rm(shost)	करो अणु पूर्ण जबतक (0)
# define scsi_init_procfs()		(0)
# define scsi_निकास_procfs()		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_PROC_FS */

/* scsi_scan.c */
बाह्य अक्षर scsi_scan_type[];
बाह्य पूर्णांक scsi_complete_async_scans(व्योम);
बाह्य पूर्णांक scsi_scan_host_selected(काष्ठा Scsi_Host *, अचिन्हित पूर्णांक,
				   अचिन्हित पूर्णांक, u64, क्रमागत scsi_scan_mode);
बाह्य व्योम scsi_क्रमget_host(काष्ठा Scsi_Host *);
बाह्य व्योम scsi_rescan_device(काष्ठा device *);

/* scsi_sysctl.c */
#अगर_घोषित CONFIG_SYSCTL
बाह्य पूर्णांक scsi_init_sysctl(व्योम);
बाह्य व्योम scsi_निकास_sysctl(व्योम);
#अन्यथा
# define scsi_init_sysctl()		(0)
# define scsi_निकास_sysctl()		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_SYSCTL */

/* scsi_sysfs.c */
बाह्य पूर्णांक scsi_sysfs_add_sdev(काष्ठा scsi_device *);
बाह्य पूर्णांक scsi_sysfs_add_host(काष्ठा Scsi_Host *);
बाह्य पूर्णांक scsi_sysfs_रेजिस्टर(व्योम);
बाह्य व्योम scsi_sysfs_unरेजिस्टर(व्योम);
बाह्य व्योम scsi_sysfs_device_initialize(काष्ठा scsi_device *);
बाह्य पूर्णांक scsi_sysfs_target_initialize(काष्ठा scsi_device *);
बाह्य काष्ठा scsi_transport_ढाँचा blank_transport_ढाँचा;
बाह्य व्योम __scsi_हटाओ_device(काष्ठा scsi_device *);

बाह्य काष्ठा bus_type scsi_bus_type;
बाह्य स्थिर काष्ठा attribute_group *scsi_sysfs_shost_attr_groups[];

/* scsi_netlink.c */
#अगर_घोषित CONFIG_SCSI_NETLINK
बाह्य व्योम scsi_netlink_init(व्योम);
बाह्य व्योम scsi_netlink_निकास(व्योम);
बाह्य काष्ठा sock *scsi_nl_sock;
#अन्यथा
अटल अंतरभूत व्योम scsi_netlink_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम scsi_netlink_निकास(व्योम) अणुपूर्ण
#पूर्ण_अगर

/* scsi_pm.c */
#अगर_घोषित CONFIG_PM
बाह्य स्थिर काष्ठा dev_pm_ops scsi_bus_pm_ops;

बाह्य व्योम scsi_स्वतःpm_get_target(काष्ठा scsi_target *);
बाह्य व्योम scsi_स्वतःpm_put_target(काष्ठा scsi_target *);
बाह्य पूर्णांक scsi_स्वतःpm_get_host(काष्ठा Scsi_Host *);
बाह्य व्योम scsi_स्वतःpm_put_host(काष्ठा Scsi_Host *);
#अन्यथा
अटल अंतरभूत व्योम scsi_स्वतःpm_get_target(काष्ठा scsi_target *t) अणुपूर्ण
अटल अंतरभूत व्योम scsi_स्वतःpm_put_target(काष्ठा scsi_target *t) अणुपूर्ण
अटल अंतरभूत पूर्णांक scsi_स्वतःpm_get_host(काष्ठा Scsi_Host *h) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम scsi_स्वतःpm_put_host(काष्ठा Scsi_Host *h) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PM */

बाह्य काष्ठा async_करोमुख्य scsi_sd_pm_करोमुख्य;

/* scsi_dh.c */
#अगर_घोषित CONFIG_SCSI_DH
व्योम scsi_dh_add_device(काष्ठा scsi_device *sdev);
व्योम scsi_dh_release_device(काष्ठा scsi_device *sdev);
#अन्यथा
अटल अंतरभूत व्योम scsi_dh_add_device(काष्ठा scsi_device *sdev) अणु पूर्ण
अटल अंतरभूत व्योम scsi_dh_release_device(काष्ठा scsi_device *sdev) अणु पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक scsi_device_max_queue_depth(काष्ठा scsi_device *sdev);

/* 
 * पूर्णांकernal scsi समयout functions: क्रम use by mid-layer and transport
 * classes.
 */

#घोषणा SCSI_DEVICE_BLOCK_MAX_TIMEOUT	600	/* units in seconds */

#पूर्ण_अगर /* _SCSI_PRIV_H */
