<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */

#अगर_अघोषित __BFAD_IM_H__
#घोषणा __BFAD_IM_H__

#समावेश "bfa_fcs.h"

#घोषणा FCPI_NAME " fcpim"

#अगर_अघोषित KOBJ_NAME_LEN
#घोषणा KOBJ_NAME_LEN           20
#पूर्ण_अगर

bfa_status_t bfad_im_module_init(व्योम);
व्योम bfad_im_module_निकास(व्योम);
bfa_status_t bfad_im_probe(काष्ठा bfad_s *bfad);
व्योम bfad_im_probe_unकरो(काष्ठा bfad_s *bfad);
bfa_status_t bfad_im_port_new(काष्ठा bfad_s *bfad, काष्ठा bfad_port_s *port);
व्योम bfad_im_port_delete(काष्ठा bfad_s *bfad, काष्ठा bfad_port_s *port);
व्योम bfad_im_port_clean(काष्ठा bfad_im_port_s *im_port);
पूर्णांक  bfad_im_scsi_host_alloc(काष्ठा bfad_s *bfad,
		काष्ठा bfad_im_port_s *im_port, काष्ठा device *dev);
व्योम bfad_im_scsi_host_मुक्त(काष्ठा bfad_s *bfad,
				काष्ठा bfad_im_port_s *im_port);
u32 bfad_im_supported_speeds(काष्ठा bfa_s *bfa);

#घोषणा MAX_FCP_TARGET 1024
#घोषणा MAX_FCP_LUN 16384
#घोषणा BFAD_TARGET_RESET_TMO 60
#घोषणा BFAD_LUN_RESET_TMO 60
#घोषणा BFA_QUEUE_FULL_RAMP_UP_TIME 120

/*
 * itnim flags
 */
#घोषणा IO_DONE_BIT			0

काष्ठा bfad_itnim_data_s अणु
	काष्ठा bfad_itnim_s *itnim;
पूर्ण;

काष्ठा bfad_im_port_s अणु
	काष्ठा bfad_s         *bfad;
	काष्ठा bfad_port_s    *port;
	काष्ठा work_काष्ठा port_delete_work;
	पूर्णांक             idr_id;
	u16        cur_scsi_id;
	u16	flags;
	काष्ठा list_head binding_list;
	काष्ठा Scsi_Host *shost;
	काष्ठा list_head itnim_mapped_list;
	काष्ठा fc_vport *fc_vport;
पूर्ण;

काष्ठा bfad_im_port_poपूर्णांकer अणु
	काष्ठा bfad_im_port_s *p;
पूर्ण;

अटल अंतरभूत काष्ठा bfad_im_port_s *bfad_get_im_port(काष्ठा Scsi_Host *host)
अणु
	काष्ठा bfad_im_port_poपूर्णांकer *im_portp = shost_priv(host);
	वापस im_portp->p;
पूर्ण

क्रमागत bfad_itnim_state अणु
	ITNIM_STATE_NONE,
	ITNIM_STATE_ONLINE,
	ITNIM_STATE_OFFLINE_PENDING,
	ITNIM_STATE_OFFLINE,
	ITNIM_STATE_TIMEOUT,
	ITNIM_STATE_FREE,
पूर्ण;

/*
 * Per itnim data काष्ठाure
 */
काष्ठा bfad_itnim_s अणु
	काष्ठा list_head list_entry;
	काष्ठा bfa_fcs_itnim_s fcs_itnim;
	काष्ठा work_काष्ठा itnim_work;
	u32        flags;
	क्रमागत bfad_itnim_state state;
	काष्ठा bfad_im_s *im;
	काष्ठा bfad_im_port_s *im_port;
	काष्ठा bfad_rport_s *drv_rport;
	काष्ठा fc_rport *fc_rport;
	काष्ठा bfa_itnim_s *bfa_itnim;
	u16        scsi_tgt_id;
	u16	   channel;
	u16        queue_work;
	अचिन्हित दीर्घ	last_ramp_up_समय;
	अचिन्हित दीर्घ	last_queue_full_समय;
पूर्ण;

क्रमागत bfad_binding_type अणु
	FCP_PWWN_BINDING = 0x1,
	FCP_NWWN_BINDING = 0x2,
	FCP_FCID_BINDING = 0x3,
पूर्ण;

काष्ठा bfad_fcp_binding अणु
	काष्ठा list_head list_entry;
	क्रमागत bfad_binding_type binding_type;
	u16        scsi_target_id;
	u32        fc_id;
	wwn_t           nwwn;
	wwn_t           pwwn;
पूर्ण;

काष्ठा bfad_im_s अणु
	काष्ठा bfad_s         *bfad;
	काष्ठा workqueue_काष्ठा *drv_workq;
	अक्षर            drv_workq_name[KOBJ_NAME_LEN];
	काष्ठा work_काष्ठा	aen_im_notअगरy_work;
पूर्ण;

#घोषणा bfad_get_aen_entry(_drv, _entry) करो अणु				\
	अचिन्हित दीर्घ	_flags;						\
	spin_lock_irqsave(&(_drv)->bfad_aen_spinlock, _flags);		\
	bfa_q_deq(&(_drv)->मुक्त_aen_q, &(_entry));			\
	अगर (_entry)							\
		list_add_tail(&(_entry)->qe, &(_drv)->active_aen_q);	\
	spin_unlock_irqrestore(&(_drv)->bfad_aen_spinlock, _flags);	\
पूर्ण जबतक (0)

/* post fc_host venकरोr event */
अटल अंतरभूत व्योम bfad_im_post_venकरोr_event(काष्ठा bfa_aen_entry_s *entry,
					     काष्ठा bfad_s *drv, पूर्णांक cnt,
					     क्रमागत bfa_aen_category cat,
					     पूर्णांक evt)
अणु
	काष्ठा बारpec64 ts;

	kसमय_get_real_ts64(&ts);
	/*
	 * 'unsigned long aen_tv_sec' overflows in y2106 on 32-bit
	 * architectures, or in 2038 अगर user space पूर्णांकerprets it
	 * as 'signed'.
	 */
	entry->aen_tv_sec = ts.tv_sec;
	entry->aen_tv_usec = ts.tv_nsec / NSEC_PER_USEC;
	entry->bfad_num = drv->inst_no;
	entry->seq_num = cnt;
	entry->aen_category = cat;
	entry->aen_type = evt;
	अगर (drv->bfad_flags & BFAD_FC4_PROBE_DONE)
		queue_work(drv->im->drv_workq, &drv->im->aen_im_notअगरy_work);
पूर्ण

काष्ठा Scsi_Host *bfad_scsi_host_alloc(काष्ठा bfad_im_port_s *im_port,
				काष्ठा bfad_s *);
bfa_status_t bfad_thपढ़ो_workq(काष्ठा bfad_s *bfad);
व्योम bfad_destroy_workq(काष्ठा bfad_im_s *im);
व्योम bfad_fc_host_init(काष्ठा bfad_im_port_s *im_port);
व्योम bfad_scsi_host_मुक्त(काष्ठा bfad_s *bfad,
				 काष्ठा bfad_im_port_s *im_port);
व्योम bfad_ramp_up_qdepth(काष्ठा bfad_itnim_s *itnim,
				 काष्ठा scsi_device *sdev);
व्योम bfad_handle_qfull(काष्ठा bfad_itnim_s *itnim, काष्ठा scsi_device *sdev);
काष्ठा bfad_itnim_s *bfad_get_itnim(काष्ठा bfad_im_port_s *im_port, पूर्णांक id);

बाह्य काष्ठा scsi_host_ढाँचा bfad_im_scsi_host_ढाँचा;
बाह्य काष्ठा scsi_host_ढाँचा bfad_im_vport_ढाँचा;
बाह्य काष्ठा fc_function_ढाँचा bfad_im_fc_function_ढाँचा;
बाह्य काष्ठा fc_function_ढाँचा bfad_im_vport_fc_function_ढाँचा;
बाह्य काष्ठा scsi_transport_ढाँचा *bfad_im_scsi_transport_ढाँचा;
बाह्य काष्ठा scsi_transport_ढाँचा *bfad_im_scsi_vport_transport_ढाँचा;

बाह्य काष्ठा device_attribute *bfad_im_host_attrs[];
बाह्य काष्ठा device_attribute *bfad_im_vport_attrs[];

irqवापस_t bfad_पूर्णांकx(पूर्णांक irq, व्योम *dev_id);

पूर्णांक bfad_im_bsg_request(काष्ठा bsg_job *job);
पूर्णांक bfad_im_bsg_समयout(काष्ठा bsg_job *job);

/*
 * Macro to set the SCSI device sdev_bflags - sdev_bflags are used by the
 * SCSI mid-layer to choose LUN Scanning mode REPORT_LUNS vs. Sequential Scan
 *
 * Internally iterate's over all the ITNIM's part of the im_port & set's the
 * sdev_bflags क्रम the scsi_device associated with LUN #0.
 */
#घोषणा bfad_reset_sdev_bflags(__im_port, __lunmask_cfg) करो अणु		\
	काष्ठा scsi_device *__sdev = शून्य;				\
	काष्ठा bfad_itnim_s *__itnim = शून्य;				\
	u32 scan_flags = BLIST_NOREPORTLUN | BLIST_SPARSELUN;		\
	list_क्रम_each_entry(__itnim, &((__im_port)->itnim_mapped_list),	\
			    list_entry) अणु				\
		__sdev = scsi_device_lookup((__im_port)->shost,		\
					    __itnim->channel,		\
					    __itnim->scsi_tgt_id, 0);	\
		अगर (__sdev) अणु						\
			अगर ((__lunmask_cfg) == BFA_TRUE)		\
				__sdev->sdev_bflags |= scan_flags;	\
			अन्यथा						\
				__sdev->sdev_bflags &= ~scan_flags;	\
			scsi_device_put(__sdev);			\
		पूर्ण							\
	पूर्ण								\
पूर्ण जबतक (0)

#पूर्ण_अगर
