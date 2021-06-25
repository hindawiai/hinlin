<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_TIMER_H
#घोषणा __SOUND_TIMER_H

/*
 *  Timer असलtract layer
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>,
 *		     Abramo Bagnara <abramo@alsa-project.org>
 */

#समावेश <sound/asound.h>
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा snd_समयr_chip(समयr) ((समयr)->निजी_data)

#घोषणा SNDRV_TIMER_DEVICES	16

#घोषणा SNDRV_TIMER_DEV_FLG_PCM	0x10000000

#घोषणा SNDRV_TIMER_HW_AUTO	0x00000001	/* स्वतः trigger is supported */
#घोषणा SNDRV_TIMER_HW_STOP	0x00000002	/* call stop beक्रमe start */
#घोषणा SNDRV_TIMER_HW_SLAVE	0x00000004	/* only slave समयr (variable resolution) */
#घोषणा SNDRV_TIMER_HW_FIRST	0x00000008	/* first tick can be incomplete */
#घोषणा SNDRV_TIMER_HW_WORK	0x00000010	/* समयr is called from work */

#घोषणा SNDRV_TIMER_IFLG_SLAVE	  0x00000001
#घोषणा SNDRV_TIMER_IFLG_RUNNING  0x00000002
#घोषणा SNDRV_TIMER_IFLG_START	  0x00000004
#घोषणा SNDRV_TIMER_IFLG_AUTO	  0x00000008	/* स्वतः restart */
#घोषणा SNDRV_TIMER_IFLG_FAST	  0x00000010	/* fast callback (करो not use work) */
#घोषणा SNDRV_TIMER_IFLG_CALLBACK 0x00000020	/* समयr callback is active */
#घोषणा SNDRV_TIMER_IFLG_EXCLUSIVE 0x00000040	/* exclusive owner - no more instances */
#घोषणा SNDRV_TIMER_IFLG_EARLY_EVENT 0x00000080	/* ग_लिखो early event to the poll queue */

#घोषणा SNDRV_TIMER_FLG_CHANGE	0x00000001
#घोषणा SNDRV_TIMER_FLG_RESCHED	0x00000002	/* need reschedule */

काष्ठा snd_समयr;

काष्ठा snd_समयr_hardware अणु
	/* -- must be filled with low-level driver */
	अचिन्हित पूर्णांक flags;		/* various flags */
	अचिन्हित दीर्घ resolution;	/* average समयr resolution क्रम one tick in nsec */
	अचिन्हित दीर्घ resolution_min;	/* minimal resolution */
	अचिन्हित दीर्घ resolution_max;	/* maximal resolution */
	अचिन्हित दीर्घ ticks;		/* max समयr ticks per पूर्णांकerrupt */
	/* -- low-level functions -- */
	पूर्णांक (*खोलो) (काष्ठा snd_समयr * समयr);
	पूर्णांक (*बंद) (काष्ठा snd_समयr * समयr);
	अचिन्हित दीर्घ (*c_resolution) (काष्ठा snd_समयr * समयr);
	पूर्णांक (*start) (काष्ठा snd_समयr * समयr);
	पूर्णांक (*stop) (काष्ठा snd_समयr * समयr);
	पूर्णांक (*set_period) (काष्ठा snd_समयr * समयr, अचिन्हित दीर्घ period_num, अचिन्हित दीर्घ period_den);
	पूर्णांक (*precise_resolution) (काष्ठा snd_समयr * समयr, अचिन्हित दीर्घ *num, अचिन्हित दीर्घ *den);
पूर्ण;

काष्ठा snd_समयr अणु
	पूर्णांक पंचांगr_class;
	काष्ठा snd_card *card;
	काष्ठा module *module;
	पूर्णांक पंचांगr_device;
	पूर्णांक पंचांगr_subdevice;
	अक्षर id[64];
	अक्षर name[80];
	अचिन्हित पूर्णांक flags;
	पूर्णांक running;			/* running instances */
	अचिन्हित दीर्घ sticks;		/* schedule ticks */
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त) (काष्ठा snd_समयr *समयr);
	काष्ठा snd_समयr_hardware hw;
	spinlock_t lock;
	काष्ठा list_head device_list;
	काष्ठा list_head खोलो_list_head;
	काष्ठा list_head active_list_head;
	काष्ठा list_head ack_list_head;
	काष्ठा list_head sack_list_head; /* slow ack list head */
	काष्ठा work_काष्ठा task_work;
	पूर्णांक max_instances;	/* upper limit of समयr instances */
	पूर्णांक num_instances;	/* current number of समयr instances */
पूर्ण;

काष्ठा snd_समयr_instance अणु
	काष्ठा snd_समयr *समयr;
	अक्षर *owner;
	अचिन्हित पूर्णांक flags;
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त) (काष्ठा snd_समयr_instance *ti);
	व्योम (*callback) (काष्ठा snd_समयr_instance *समयri,
			  अचिन्हित दीर्घ ticks, अचिन्हित दीर्घ resolution);
	व्योम (*ccallback) (काष्ठा snd_समयr_instance * समयri,
			   पूर्णांक event,
			   काष्ठा बारpec64 * tstamp,
			   अचिन्हित दीर्घ resolution);
	व्योम (*disconnect)(काष्ठा snd_समयr_instance *समयri);
	व्योम *callback_data;
	अचिन्हित दीर्घ ticks;		/* स्वतः-load ticks when expired */
	अचिन्हित दीर्घ cticks;		/* current ticks */
	अचिन्हित दीर्घ pticks;		/* accumulated ticks क्रम callback */
	अचिन्हित दीर्घ resolution;	/* current resolution क्रम work */
	अचिन्हित दीर्घ lost;		/* lost ticks */
	पूर्णांक slave_class;
	अचिन्हित पूर्णांक slave_id;
	काष्ठा list_head खोलो_list;
	काष्ठा list_head active_list;
	काष्ठा list_head ack_list;
	काष्ठा list_head slave_list_head;
	काष्ठा list_head slave_active_head;
	काष्ठा snd_समयr_instance *master;
पूर्ण;

/*
 *  Registering
 */

पूर्णांक snd_समयr_new(काष्ठा snd_card *card, अक्षर *id, काष्ठा snd_समयr_id *tid, काष्ठा snd_समयr **rसमयr);
व्योम snd_समयr_notअगरy(काष्ठा snd_समयr *समयr, पूर्णांक event, काष्ठा बारpec64 *tstamp);
पूर्णांक snd_समयr_global_new(अक्षर *id, पूर्णांक device, काष्ठा snd_समयr **rसमयr);
पूर्णांक snd_समयr_global_मुक्त(काष्ठा snd_समयr *समयr);
पूर्णांक snd_समयr_global_रेजिस्टर(काष्ठा snd_समयr *समयr);

काष्ठा snd_समयr_instance *snd_समयr_instance_new(स्थिर अक्षर *owner);
व्योम snd_समयr_instance_मुक्त(काष्ठा snd_समयr_instance *समयri);
पूर्णांक snd_समयr_खोलो(काष्ठा snd_समयr_instance *समयri, काष्ठा snd_समयr_id *tid, अचिन्हित पूर्णांक slave_id);
व्योम snd_समयr_बंद(काष्ठा snd_समयr_instance *समयri);
अचिन्हित दीर्घ snd_समयr_resolution(काष्ठा snd_समयr_instance *समयri);
पूर्णांक snd_समयr_start(काष्ठा snd_समयr_instance *समयri, अचिन्हित पूर्णांक ticks);
पूर्णांक snd_समयr_stop(काष्ठा snd_समयr_instance *समयri);
पूर्णांक snd_समयr_जारी(काष्ठा snd_समयr_instance *समयri);
पूर्णांक snd_समयr_छोड़ो(काष्ठा snd_समयr_instance *समयri);

व्योम snd_समयr_पूर्णांकerrupt(काष्ठा snd_समयr *समयr, अचिन्हित दीर्घ ticks_left);

#पूर्ण_अगर /* __SOUND_TIMER_H */
