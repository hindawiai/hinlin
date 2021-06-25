<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  libata.h - helper library क्रम ATA
 *
 *  Copyright 2003-2004 Red Hat, Inc.  All rights reserved.
 *  Copyright 2003-2004 Jeff Garzik
 *
 *  libata करोcumentation is available via 'make {ps|pdf}docs',
 *  as Documentation/driver-api/libata.rst
 */

#अगर_अघोषित __LIBATA_H__
#घोषणा __LIBATA_H__

#घोषणा DRV_NAME	"libata"
#घोषणा DRV_VERSION	"3.00"	/* must be exactly four अक्षरs */

/* libata-core.c */
क्रमागत अणु
	/* flags क्रम ata_dev_पढ़ो_id() */
	ATA_READID_POSTRESET	= (1 << 0), /* पढ़ोing ID after reset */

	/* selector क्रम ata_करोwn_xfermask_limit() */
	ATA_DNXFER_PIO		= 0,	/* speed करोwn PIO */
	ATA_DNXFER_DMA		= 1,	/* speed करोwn DMA */
	ATA_DNXFER_40C		= 2,	/* apply 40c cable limit */
	ATA_DNXFER_FORCE_PIO	= 3,	/* क्रमce PIO */
	ATA_DNXFER_FORCE_PIO0	= 4,	/* क्रमce PIO0 */

	ATA_DNXFER_QUIET	= (1 << 31),
पूर्ण;

बाह्य atomic_t ata_prपूर्णांक_id;
बाह्य पूर्णांक atapi_passthru16;
बाह्य पूर्णांक libata_fua;
बाह्य पूर्णांक libata_noacpi;
बाह्य पूर्णांक libata_allow_tpm;
बाह्य स्थिर काष्ठा device_type ata_port_type;
बाह्य काष्ठा ata_link *ata_dev_phys_link(काष्ठा ata_device *dev);
#अगर_घोषित CONFIG_ATA_FORCE
बाह्य व्योम ata_क्रमce_cbl(काष्ठा ata_port *ap);
#अन्यथा
अटल अंतरभूत व्योम ata_क्रमce_cbl(काष्ठा ata_port *ap) अणु पूर्ण
#पूर्ण_अगर
बाह्य u64 ata_tf_to_lba(स्थिर काष्ठा ata_taskfile *tf);
बाह्य u64 ata_tf_to_lba48(स्थिर काष्ठा ata_taskfile *tf);
बाह्य काष्ठा ata_queued_cmd *ata_qc_new_init(काष्ठा ata_device *dev, पूर्णांक tag);
बाह्य पूर्णांक ata_build_rw_tf(काष्ठा ata_taskfile *tf, काष्ठा ata_device *dev,
			   u64 block, u32 n_block, अचिन्हित पूर्णांक tf_flags,
			   अचिन्हित पूर्णांक tag, पूर्णांक class);
बाह्य u64 ata_tf_पढ़ो_block(स्थिर काष्ठा ata_taskfile *tf,
			     काष्ठा ata_device *dev);
बाह्य अचिन्हित ata_exec_पूर्णांकernal(काष्ठा ata_device *dev,
				  काष्ठा ata_taskfile *tf, स्थिर u8 *cdb,
				  पूर्णांक dma_dir, व्योम *buf, अचिन्हित पूर्णांक buflen,
				  अचिन्हित दीर्घ समयout);
बाह्य अचिन्हित ata_exec_पूर्णांकernal_sg(काष्ठा ata_device *dev,
				     काष्ठा ata_taskfile *tf, स्थिर u8 *cdb,
				     पूर्णांक dma_dir, काष्ठा scatterlist *sg,
				     अचिन्हित पूर्णांक n_elem, अचिन्हित दीर्घ समयout);
बाह्य पूर्णांक ata_रुको_पढ़ोy(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline,
			  पूर्णांक (*check_पढ़ोy)(काष्ठा ata_link *link));
बाह्य पूर्णांक ata_dev_पढ़ो_id(काष्ठा ata_device *dev, अचिन्हित पूर्णांक *p_class,
			   अचिन्हित पूर्णांक flags, u16 *id);
बाह्य पूर्णांक ata_dev_reपढ़ो_id(काष्ठा ata_device *dev, अचिन्हित पूर्णांक पढ़ोid_flags);
बाह्य पूर्णांक ata_dev_revalidate(काष्ठा ata_device *dev, अचिन्हित पूर्णांक new_class,
			      अचिन्हित पूर्णांक पढ़ोid_flags);
बाह्य पूर्णांक ata_dev_configure(काष्ठा ata_device *dev);
बाह्य पूर्णांक sata_करोwn_spd_limit(काष्ठा ata_link *link, u32 spd_limit);
बाह्य पूर्णांक ata_करोwn_xfermask_limit(काष्ठा ata_device *dev, अचिन्हित पूर्णांक sel);
बाह्य अचिन्हित पूर्णांक ata_dev_set_feature(काष्ठा ata_device *dev,
					u8 enable, u8 feature);
बाह्य व्योम ata_qc_मुक्त(काष्ठा ata_queued_cmd *qc);
बाह्य व्योम ata_qc_issue(काष्ठा ata_queued_cmd *qc);
बाह्य व्योम __ata_qc_complete(काष्ठा ata_queued_cmd *qc);
बाह्य पूर्णांक atapi_check_dma(काष्ठा ata_queued_cmd *qc);
बाह्य व्योम swap_buf_le16(u16 *buf, अचिन्हित पूर्णांक buf_words);
बाह्य bool ata_phys_link_online(काष्ठा ata_link *link);
बाह्य bool ata_phys_link_offline(काष्ठा ata_link *link);
बाह्य व्योम ata_dev_init(काष्ठा ata_device *dev);
बाह्य व्योम ata_link_init(काष्ठा ata_port *ap, काष्ठा ata_link *link, पूर्णांक pmp);
बाह्य पूर्णांक sata_link_init_spd(काष्ठा ata_link *link);
बाह्य पूर्णांक ata_task_ioctl(काष्ठा scsi_device *scsidev, व्योम __user *arg);
बाह्य पूर्णांक ata_cmd_ioctl(काष्ठा scsi_device *scsidev, व्योम __user *arg);
बाह्य काष्ठा ata_port *ata_port_alloc(काष्ठा ata_host *host);
बाह्य स्थिर अक्षर *sata_spd_string(अचिन्हित पूर्णांक spd);
बाह्य पूर्णांक ata_port_probe(काष्ठा ata_port *ap);
बाह्य व्योम __ata_port_probe(काष्ठा ata_port *ap);
बाह्य अचिन्हित पूर्णांक ata_पढ़ो_log_page(काष्ठा ata_device *dev, u8 log,
				      u8 page, व्योम *buf, अचिन्हित पूर्णांक sectors);

#घोषणा to_ata_port(d) container_of(d, काष्ठा ata_port, tdev)

/* libata-sata.c */
#अगर_घोषित CONFIG_SATA_HOST
पूर्णांक ata_sas_allocate_tag(काष्ठा ata_port *ap);
व्योम ata_sas_मुक्त_tag(अचिन्हित पूर्णांक tag, काष्ठा ata_port *ap);
#अन्यथा
अटल अंतरभूत पूर्णांक ata_sas_allocate_tag(काष्ठा ata_port *ap)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत व्योम ata_sas_मुक्त_tag(अचिन्हित पूर्णांक tag, काष्ठा ata_port *ap) अणु पूर्ण
#पूर्ण_अगर

/* libata-acpi.c */
#अगर_घोषित CONFIG_ATA_ACPI
बाह्य अचिन्हित पूर्णांक ata_acpi_gtf_filter;
बाह्य व्योम ata_acpi_dissociate(काष्ठा ata_host *host);
बाह्य पूर्णांक ata_acpi_on_suspend(काष्ठा ata_port *ap);
बाह्य व्योम ata_acpi_on_resume(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_acpi_on_devcfg(काष्ठा ata_device *dev);
बाह्य व्योम ata_acpi_on_disable(काष्ठा ata_device *dev);
बाह्य व्योम ata_acpi_set_state(काष्ठा ata_port *ap, pm_message_t state);
बाह्य व्योम ata_acpi_bind_port(काष्ठा ata_port *ap);
बाह्य व्योम ata_acpi_bind_dev(काष्ठा ata_device *dev);
बाह्य acpi_handle ata_dev_acpi_handle(काष्ठा ata_device *dev);
#अन्यथा
अटल अंतरभूत व्योम ata_acpi_dissociate(काष्ठा ata_host *host) अणु पूर्ण
अटल अंतरभूत पूर्णांक ata_acpi_on_suspend(काष्ठा ata_port *ap) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ata_acpi_on_resume(काष्ठा ata_port *ap) अणु पूर्ण
अटल अंतरभूत पूर्णांक ata_acpi_on_devcfg(काष्ठा ata_device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ata_acpi_on_disable(काष्ठा ata_device *dev) अणु पूर्ण
अटल अंतरभूत व्योम ata_acpi_set_state(काष्ठा ata_port *ap,
				      pm_message_t state) अणु पूर्ण
अटल अंतरभूत व्योम ata_acpi_bind_port(काष्ठा ata_port *ap) अणुपूर्ण
अटल अंतरभूत व्योम ata_acpi_bind_dev(काष्ठा ata_device *dev) अणुपूर्ण
#पूर्ण_अगर

/* libata-scsi.c */
बाह्य काष्ठा ata_device *ata_scsi_find_dev(काष्ठा ata_port *ap,
					    स्थिर काष्ठा scsi_device *scsidev);
बाह्य पूर्णांक ata_scsi_add_hosts(काष्ठा ata_host *host,
			      काष्ठा scsi_host_ढाँचा *sht);
बाह्य व्योम ata_scsi_scan_host(काष्ठा ata_port *ap, पूर्णांक sync);
बाह्य पूर्णांक ata_scsi_offline_dev(काष्ठा ata_device *dev);
बाह्य व्योम ata_scsi_set_sense(काष्ठा ata_device *dev,
			       काष्ठा scsi_cmnd *cmd, u8 sk, u8 asc, u8 ascq);
बाह्य व्योम ata_scsi_set_sense_inक्रमmation(काष्ठा ata_device *dev,
					   काष्ठा scsi_cmnd *cmd,
					   स्थिर काष्ठा ata_taskfile *tf);
बाह्य व्योम ata_scsi_media_change_notअगरy(काष्ठा ata_device *dev);
बाह्य व्योम ata_scsi_hotplug(काष्ठा work_काष्ठा *work);
बाह्य व्योम ata_schedule_scsi_eh(काष्ठा Scsi_Host *shost);
बाह्य व्योम ata_scsi_dev_rescan(काष्ठा work_काष्ठा *work);
बाह्य पूर्णांक ata_bus_probe(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_scsi_user_scan(काष्ठा Scsi_Host *shost, अचिन्हित पूर्णांक channel,
			      अचिन्हित पूर्णांक id, u64 lun);
व्योम ata_scsi_sdev_config(काष्ठा scsi_device *sdev);
पूर्णांक ata_scsi_dev_config(काष्ठा scsi_device *sdev, काष्ठा ata_device *dev);
व्योम ata_scsi_dump_cdb(काष्ठा ata_port *ap, काष्ठा scsi_cmnd *cmd);
पूर्णांक __ata_scsi_queuecmd(काष्ठा scsi_cmnd *scmd, काष्ठा ata_device *dev);

/* libata-eh.c */
बाह्य अचिन्हित दीर्घ ata_पूर्णांकernal_cmd_समयout(काष्ठा ata_device *dev, u8 cmd);
बाह्य व्योम ata_पूर्णांकernal_cmd_समयd_out(काष्ठा ata_device *dev, u8 cmd);
बाह्य व्योम ata_eh_acquire(काष्ठा ata_port *ap);
बाह्य व्योम ata_eh_release(काष्ठा ata_port *ap);
बाह्य व्योम ata_scsi_error(काष्ठा Scsi_Host *host);
बाह्य व्योम ata_eh_fastdrain_समयrfn(काष्ठा समयr_list *t);
बाह्य व्योम ata_qc_schedule_eh(काष्ठा ata_queued_cmd *qc);
बाह्य व्योम ata_dev_disable(काष्ठा ata_device *dev);
बाह्य व्योम ata_eh_detach_dev(काष्ठा ata_device *dev);
बाह्य व्योम ata_eh_about_to_करो(काष्ठा ata_link *link, काष्ठा ata_device *dev,
			       अचिन्हित पूर्णांक action);
बाह्य व्योम ata_eh_करोne(काष्ठा ata_link *link, काष्ठा ata_device *dev,
			अचिन्हित पूर्णांक action);
बाह्य व्योम ata_eh_स्वतःpsy(काष्ठा ata_port *ap);
स्थिर अक्षर *ata_get_cmd_descript(u8 command);
बाह्य व्योम ata_eh_report(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_eh_reset(काष्ठा ata_link *link, पूर्णांक classअगरy,
			ata_prereset_fn_t prereset, ata_reset_fn_t softreset,
			ata_reset_fn_t hardreset, ata_postreset_fn_t postreset);
बाह्य पूर्णांक ata_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **r_failed_dev);
बाह्य पूर्णांक ata_eh_recover(काष्ठा ata_port *ap, ata_prereset_fn_t prereset,
			  ata_reset_fn_t softreset, ata_reset_fn_t hardreset,
			  ata_postreset_fn_t postreset,
			  काष्ठा ata_link **r_failed_disk);
बाह्य व्योम ata_eh_finish(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_ering_map(काष्ठा ata_ering *ering,
			 पूर्णांक (*map_fn)(काष्ठा ata_ering_entry *, व्योम *),
		  	 व्योम *arg);
बाह्य अचिन्हित पूर्णांक atapi_eh_tur(काष्ठा ata_device *dev, u8 *r_sense_key);
बाह्य अचिन्हित पूर्णांक atapi_eh_request_sense(काष्ठा ata_device *dev,
					   u8 *sense_buf, u8 dfl_sense_key);

/* libata-pmp.c */
#अगर_घोषित CONFIG_SATA_PMP
बाह्य पूर्णांक sata_pmp_scr_पढ़ो(काष्ठा ata_link *link, पूर्णांक reg, u32 *val);
बाह्य पूर्णांक sata_pmp_scr_ग_लिखो(काष्ठा ata_link *link, पूर्णांक reg, u32 val);
बाह्य पूर्णांक sata_pmp_set_lpm(काष्ठा ata_link *link, क्रमागत ata_lpm_policy policy,
			    अचिन्हित hपूर्णांकs);
बाह्य पूर्णांक sata_pmp_attach(काष्ठा ata_device *dev);
#अन्यथा /* CONFIG_SATA_PMP */
अटल अंतरभूत पूर्णांक sata_pmp_scr_पढ़ो(काष्ठा ata_link *link, पूर्णांक reg, u32 *val)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक sata_pmp_scr_ग_लिखो(काष्ठा ata_link *link, पूर्णांक reg, u32 val)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक sata_pmp_set_lpm(काष्ठा ata_link *link,
				   क्रमागत ata_lpm_policy policy, अचिन्हित hपूर्णांकs)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक sata_pmp_attach(काष्ठा ata_device *dev)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_SATA_PMP */

/* libata-sff.c */
#अगर_घोषित CONFIG_ATA_SFF
बाह्य व्योम ata_sff_flush_pio_task(काष्ठा ata_port *ap);
बाह्य व्योम ata_sff_port_init(काष्ठा ata_port *ap);
बाह्य पूर्णांक ata_sff_init(व्योम);
बाह्य व्योम ata_sff_निकास(व्योम);
#अन्यथा /* CONFIG_ATA_SFF */
अटल अंतरभूत व्योम ata_sff_flush_pio_task(काष्ठा ata_port *ap)
अणु पूर्ण
अटल अंतरभूत व्योम ata_sff_port_init(काष्ठा ata_port *ap)
अणु पूर्ण
अटल अंतरभूत पूर्णांक ata_sff_init(व्योम)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ata_sff_निकास(व्योम)
अणु पूर्ण
#पूर्ण_अगर /* CONFIG_ATA_SFF */

/* libata-zpodd.c */
#अगर_घोषित CONFIG_SATA_ZPODD
व्योम zpodd_init(काष्ठा ata_device *dev);
व्योम zpodd_निकास(काष्ठा ata_device *dev);
अटल अंतरभूत bool zpodd_dev_enabled(काष्ठा ata_device *dev)
अणु
	वापस dev->zpodd != शून्य;
पूर्ण
व्योम zpodd_on_suspend(काष्ठा ata_device *dev);
bool zpodd_zpपढ़ोy(काष्ठा ata_device *dev);
व्योम zpodd_enable_run_wake(काष्ठा ata_device *dev);
व्योम zpodd_disable_run_wake(काष्ठा ata_device *dev);
व्योम zpodd_post_घातeron(काष्ठा ata_device *dev);
#अन्यथा /* CONFIG_SATA_ZPODD */
अटल अंतरभूत व्योम zpodd_init(काष्ठा ata_device *dev) अणुपूर्ण
अटल अंतरभूत व्योम zpodd_निकास(काष्ठा ata_device *dev) अणुपूर्ण
अटल अंतरभूत bool zpodd_dev_enabled(काष्ठा ata_device *dev) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम zpodd_on_suspend(काष्ठा ata_device *dev) अणुपूर्ण
अटल अंतरभूत bool zpodd_zpपढ़ोy(काष्ठा ata_device *dev) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम zpodd_enable_run_wake(काष्ठा ata_device *dev) अणुपूर्ण
अटल अंतरभूत व्योम zpodd_disable_run_wake(काष्ठा ata_device *dev) अणुपूर्ण
अटल अंतरभूत व्योम zpodd_post_घातeron(काष्ठा ata_device *dev) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_SATA_ZPODD */

#पूर्ण_अगर /* __LIBATA_H__ */
