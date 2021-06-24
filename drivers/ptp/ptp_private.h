<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * PTP 1588 घड़ी support - निजी declarations क्रम the core module.
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 */
#अगर_अघोषित _PTP_PRIVATE_H_
#घोषणा _PTP_PRIVATE_H_

#समावेश <linux/cdev.h>
#समावेश <linux/device.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mutex.h>
#समावेश <linux/posix-घड़ी.h>
#समावेश <linux/ptp_घड़ी.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/समय.स>

#घोषणा PTP_MAX_TIMESTAMPS 128
#घोषणा PTP_BUF_TIMESTAMPS 30

काष्ठा बारtamp_event_queue अणु
	काष्ठा ptp_extts_event buf[PTP_MAX_TIMESTAMPS];
	पूर्णांक head;
	पूर्णांक tail;
	spinlock_t lock;
पूर्ण;

काष्ठा ptp_घड़ी अणु
	काष्ठा posix_घड़ी घड़ी;
	काष्ठा device dev;
	काष्ठा ptp_घड़ी_info *info;
	dev_t devid;
	पूर्णांक index; /* index पूर्णांकo घड़ीs.map */
	काष्ठा pps_device *pps_source;
	दीर्घ dialed_frequency; /* remembers the frequency adjusपंचांगent */
	काष्ठा बारtamp_event_queue tsevq; /* simple fअगरo क्रम समय stamps */
	काष्ठा mutex tsevq_mux; /* one process at a समय पढ़ोing the fअगरo */
	काष्ठा mutex pincfg_mux; /* protect concurrent info->pin_config access */
	रुको_queue_head_t tsev_wq;
	पूर्णांक defunct; /* tells पढ़ोers to go away when घड़ी is being हटाओd */
	काष्ठा device_attribute *pin_dev_attr;
	काष्ठा attribute **pin_attr;
	काष्ठा attribute_group pin_attr_group;
	/* 1st entry is a poपूर्णांकer to the real group, 2nd is शून्य terminator */
	स्थिर काष्ठा attribute_group *pin_attr_groups[2];
	काष्ठा kthपढ़ो_worker *kworker;
	काष्ठा kthपढ़ो_delayed_work aux_work;
पूर्ण;

/*
 * The function queue_cnt() is safe क्रम पढ़ोers to call without
 * holding q->lock. Readers use this function to verअगरy that the queue
 * is nonempty beक्रमe proceeding with a dequeue operation. The fact
 * that a ग_लिखोr might concurrently increment the tail करोes not
 * matter, since the queue reमुख्यs nonempty nonetheless.
 */
अटल अंतरभूत पूर्णांक queue_cnt(काष्ठा बारtamp_event_queue *q)
अणु
	पूर्णांक cnt = q->tail - q->head;
	वापस cnt < 0 ? PTP_MAX_TIMESTAMPS + cnt : cnt;
पूर्ण

/*
 * see ptp_अक्षरdev.c
 */

/* caller must hold pincfg_mux */
पूर्णांक ptp_set_pinfunc(काष्ठा ptp_घड़ी *ptp, अचिन्हित पूर्णांक pin,
		    क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan);

दीर्घ ptp_ioctl(काष्ठा posix_घड़ी *pc,
	       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

पूर्णांक ptp_खोलो(काष्ठा posix_घड़ी *pc, भ_शेषe_t भ_शेषe);

sमाप_प्रकार ptp_पढ़ो(काष्ठा posix_घड़ी *pc,
		 uपूर्णांक flags, अक्षर __user *buf, माप_प्रकार cnt);

__poll_t ptp_poll(काष्ठा posix_घड़ी *pc,
	      काष्ठा file *fp, poll_table *रुको);

/*
 * see ptp_sysfs.c
 */

बाह्य स्थिर काष्ठा attribute_group *ptp_groups[];

पूर्णांक ptp_populate_pin_groups(काष्ठा ptp_घड़ी *ptp);
व्योम ptp_cleanup_pin_groups(काष्ठा ptp_घड़ी *ptp);

#पूर्ण_अगर
