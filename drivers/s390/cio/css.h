<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CSS_H
#घोषणा _CSS_H

#समावेश <linux/mutex.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/chpid.h>
#समावेश <यंत्र/schid.h>

#समावेश "cio.h"

/*
 * path grouping stuff
 */
#घोषणा SPID_FUNC_SINGLE_PATH	   0x00
#घोषणा SPID_FUNC_MULTI_PATH	   0x80
#घोषणा SPID_FUNC_ESTABLISH	   0x00
#घोषणा SPID_FUNC_RESIGN	   0x40
#घोषणा SPID_FUNC_DISBAND	   0x20

#घोषणा SNID_STATE1_RESET	   0
#घोषणा SNID_STATE1_UNGROUPED	   2
#घोषणा SNID_STATE1_GROUPED	   3

#घोषणा SNID_STATE2_NOT_RESVD	   0
#घोषणा SNID_STATE2_RESVD_ELSE	   2
#घोषणा SNID_STATE2_RESVD_SELF	   3

#घोषणा SNID_STATE3_MULTI_PATH	   1
#घोषणा SNID_STATE3_SINGLE_PATH	   0

काष्ठा path_state अणु
	__u8  state1 : 2;	/* path state value 1 */
	__u8  state2 : 2;	/* path state value 2 */
	__u8  state3 : 1;	/* path state value 3 */
	__u8  resvd  : 3;	/* reserved */
पूर्ण __attribute__ ((packed));

काष्ठा extended_cssid अणु
	u8 version;
	u8 cssid;
पूर्ण __attribute__ ((packed));

काष्ठा pgid अणु
	जोड़ अणु
		__u8 fc;   	/* SPID function code */
		काष्ठा path_state ps;	/* SNID path state */
	पूर्ण __attribute__ ((packed)) inf;
	जोड़ अणु
		__u32 cpu_addr	: 16;	/* CPU address */
		काष्ठा extended_cssid ext_cssid;
	पूर्ण __attribute__ ((packed)) pgid_high;
	__u32 cpu_id	: 24;	/* CPU identअगरication */
	__u32 cpu_model : 16;	/* CPU model */
	__u32 tod_high;		/* high word TOD घड़ी */
पूर्ण __attribute__ ((packed));

काष्ठा subchannel;
काष्ठा chp_link;
/**
 * काष्ठा css_driver - device driver क्रम subchannels
 * @subchannel_type: subchannel type supported by this driver
 * @drv: embedded device driver काष्ठाure
 * @irq: called on पूर्णांकerrupts
 * @chp_event: called क्रम events affecting a channel path
 * @sch_event: called क्रम events affecting the subchannel
 * @probe: function called on probe
 * @हटाओ: function called on हटाओ
 * @shutकरोwn: called at device shutकरोwn
 * @settle: रुको क्रम asynchronous work to finish
 */
काष्ठा css_driver अणु
	काष्ठा css_device_id *subchannel_type;
	काष्ठा device_driver drv;
	व्योम (*irq)(काष्ठा subchannel *);
	पूर्णांक (*chp_event)(काष्ठा subchannel *, काष्ठा chp_link *, पूर्णांक);
	पूर्णांक (*sch_event)(काष्ठा subchannel *, पूर्णांक);
	पूर्णांक (*probe)(काष्ठा subchannel *);
	पूर्णांक (*हटाओ)(काष्ठा subchannel *);
	व्योम (*shutकरोwn)(काष्ठा subchannel *);
	पूर्णांक (*settle)(व्योम);
पूर्ण;

#घोषणा to_cssdriver(n) container_of(n, काष्ठा css_driver, drv)

बाह्य पूर्णांक css_driver_रेजिस्टर(काष्ठा css_driver *);
बाह्य व्योम css_driver_unरेजिस्टर(काष्ठा css_driver *);

बाह्य व्योम css_sch_device_unरेजिस्टर(काष्ठा subchannel *);
बाह्य पूर्णांक css_रेजिस्टर_subchannel(काष्ठा subchannel *);
बाह्य काष्ठा subchannel *css_alloc_subchannel(काष्ठा subchannel_id,
					       काष्ठा schib *schib);
बाह्य काष्ठा subchannel *get_subchannel_by_schid(काष्ठा subchannel_id);
बाह्य पूर्णांक css_init_करोne;
बाह्य पूर्णांक max_ssid;
पूर्णांक क्रम_each_subchannel_staged(पूर्णांक (*fn_known)(काष्ठा subchannel *, व्योम *),
			       पूर्णांक (*fn_unknown)(काष्ठा subchannel_id,
			       व्योम *), व्योम *data);
बाह्य पूर्णांक क्रम_each_subchannel(पूर्णांक(*fn)(काष्ठा subchannel_id, व्योम *), व्योम *);
व्योम css_update_ssd_info(काष्ठा subchannel *sch);

काष्ठा channel_subप्रणाली अणु
	u8 cssid;
	u8 iid;
	bool id_valid; /* cssid,iid */
	काष्ठा channel_path *chps[__MAX_CHPID + 1];
	काष्ठा device device;
	काष्ठा pgid global_pgid;
	काष्ठा mutex mutex;
	/* channel measurement related */
	पूर्णांक cm_enabled;
	व्योम *cub_addr1;
	व्योम *cub_addr2;
	/* क्रम orphaned ccw devices */
	काष्ठा subchannel *pseuकरो_subchannel;
पूर्ण;
#घोषणा to_css(dev) container_of(dev, काष्ठा channel_subप्रणाली, device)

बाह्य काष्ठा channel_subप्रणाली *channel_subप्रणालीs[];

/* Dummy helper which needs to change once we support more than one css. */
अटल अंतरभूत काष्ठा channel_subप्रणाली *css_by_id(u8 cssid)
अणु
	वापस channel_subप्रणालीs[0];
पूर्ण

/* Dummy iterator which needs to change once we support more than one css. */
#घोषणा क्रम_each_css(css)						\
	क्रम ((css) = channel_subप्रणालीs[0]; (css); (css) = शून्य)

/* Helper functions to build lists क्रम the slow path. */
व्योम css_schedule_eval(काष्ठा subchannel_id schid);
व्योम css_schedule_eval_all(व्योम);
व्योम css_schedule_eval_all_unreg(अचिन्हित दीर्घ delay);
पूर्णांक css_complete_work(व्योम);

पूर्णांक sch_is_pseuकरो_sch(काष्ठा subchannel *);
काष्ठा schib;
पूर्णांक css_sch_is_valid(काष्ठा schib *);

बाह्य काष्ठा workqueue_काष्ठा *cio_work_q;
व्योम css_रुको_क्रम_slow_path(व्योम);
व्योम css_sched_sch_toकरो(काष्ठा subchannel *sch, क्रमागत sch_toकरो toकरो);
#पूर्ण_अगर
