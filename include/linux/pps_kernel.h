<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * PPS API kernel header
 *
 * Copyright (C) 2009   Roकरोlfo Giometti <giometti@linux.it>
 */

#अगर_अघोषित LINUX_PPS_KERNEL_H
#घोषणा LINUX_PPS_KERNEL_H

#समावेश <linux/pps.h>
#समावेश <linux/cdev.h>
#समावेश <linux/device.h>
#समावेश <linux/समय.स>

/*
 * Global defines
 */

काष्ठा pps_device;

/* The specअगरic PPS source info */
काष्ठा pps_source_info अणु
	अक्षर name[PPS_MAX_NAME_LEN];		/* symbolic name */
	अक्षर path[PPS_MAX_NAME_LEN];		/* path of connected device */
	पूर्णांक mode;				/* PPS allowed mode */

	व्योम (*echo)(काष्ठा pps_device *pps,
			पूर्णांक event, व्योम *data);	/* PPS echo function */

	काष्ठा module *owner;
	काष्ठा device *dev;		/* Parent device क्रम device_create */
पूर्ण;

काष्ठा pps_event_समय अणु
#अगर_घोषित CONFIG_NTP_PPS
	काष्ठा बारpec64 ts_raw;
#पूर्ण_अगर /* CONFIG_NTP_PPS */
	काष्ठा बारpec64 ts_real;
पूर्ण;

/* The मुख्य काष्ठा */
काष्ठा pps_device अणु
	काष्ठा pps_source_info info;		/* PSS source info */

	काष्ठा pps_kparams params;		/* PPS current params */

	__u32 निश्चित_sequence;			/* PPS निश्चित event seq # */
	__u32 clear_sequence;			/* PPS clear event seq # */
	काष्ठा pps_kसमय निश्चित_tu;
	काष्ठा pps_kसमय clear_tu;
	पूर्णांक current_mode;			/* PPS mode at event समय */

	अचिन्हित पूर्णांक last_ev;			/* last PPS event id */
	रुको_queue_head_t queue;		/* PPS event queue */

	अचिन्हित पूर्णांक id;			/* PPS source unique ID */
	व्योम स्थिर *lookup_cookie;		/* For pps_lookup_dev() only */
	काष्ठा cdev cdev;
	काष्ठा device *dev;
	काष्ठा fasync_काष्ठा *async_queue;	/* fasync method */
	spinlock_t lock;
पूर्ण;

/*
 * Global variables
 */

बाह्य स्थिर काष्ठा attribute_group *pps_groups[];

/*
 * Internal functions.
 *
 * These are not actually part of the exported API, but this is a
 * convenient header file to put them in.
 */

बाह्य पूर्णांक pps_रेजिस्टर_cdev(काष्ठा pps_device *pps);
बाह्य व्योम pps_unरेजिस्टर_cdev(काष्ठा pps_device *pps);

/*
 * Exported functions
 */

बाह्य काष्ठा pps_device *pps_रेजिस्टर_source(
		काष्ठा pps_source_info *info, पूर्णांक शेष_params);
बाह्य व्योम pps_unरेजिस्टर_source(काष्ठा pps_device *pps);
बाह्य व्योम pps_event(काष्ठा pps_device *pps,
		काष्ठा pps_event_समय *ts, पूर्णांक event, व्योम *data);
/* Look up a pps_device by magic cookie */
काष्ठा pps_device *pps_lookup_dev(व्योम स्थिर *cookie);

अटल अंतरभूत व्योम बारpec_to_pps_kसमय(काष्ठा pps_kसमय *kt,
		काष्ठा बारpec64 ts)
अणु
	kt->sec = ts.tv_sec;
	kt->nsec = ts.tv_nsec;
पूर्ण

अटल अंतरभूत व्योम pps_get_ts(काष्ठा pps_event_समय *ts)
अणु
	काष्ठा प्रणाली_समय_snapshot snap;

	kसमय_get_snapshot(&snap);
	ts->ts_real = kसमय_प्रकारo_बारpec64(snap.real);
#अगर_घोषित CONFIG_NTP_PPS
	ts->ts_raw = kसमय_प्रकारo_बारpec64(snap.raw);
#पूर्ण_अगर
पूर्ण

/* Subtract known समय delay from PPS event समय(s) */
अटल अंतरभूत व्योम pps_sub_ts(काष्ठा pps_event_समय *ts, काष्ठा बारpec64 delta)
अणु
	ts->ts_real = बारpec64_sub(ts->ts_real, delta);
#अगर_घोषित CONFIG_NTP_PPS
	ts->ts_raw = बारpec64_sub(ts->ts_raw, delta);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* LINUX_PPS_KERNEL_H */
