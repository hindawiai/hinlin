<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Remote Controller core raw events header
 *
 * Copyright (C) 2010 by Mauro Carvalho Chehab
 */

#अगर_अघोषित _RC_CORE_PRIV
#घोषणा _RC_CORE_PRIV

#घोषणा	RC_DEV_MAX		256
/* Define the max number of pulse/space transitions to buffer */
#घोषणा	MAX_IR_EVENT_SIZE	512

#समावेश <linux/slab.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <media/rc-core.h>

/**
 * rc_खोलो - Opens a RC device
 *
 * @rdev: poपूर्णांकer to काष्ठा rc_dev.
 */
पूर्णांक rc_खोलो(काष्ठा rc_dev *rdev);

/**
 * rc_बंद - Closes a RC device
 *
 * @rdev: poपूर्णांकer to काष्ठा rc_dev.
 */
व्योम rc_बंद(काष्ठा rc_dev *rdev);

काष्ठा ir_raw_handler अणु
	काष्ठा list_head list;

	u64 protocols; /* which are handled by this handler */
	पूर्णांक (*decode)(काष्ठा rc_dev *dev, काष्ठा ir_raw_event event);
	पूर्णांक (*encode)(क्रमागत rc_proto protocol, u32 scancode,
		      काष्ठा ir_raw_event *events, अचिन्हित पूर्णांक max);
	u32 carrier;
	u32 min_समयout;

	/* These two should only be used by the mce kbd decoder */
	पूर्णांक (*raw_रेजिस्टर)(काष्ठा rc_dev *dev);
	पूर्णांक (*raw_unरेजिस्टर)(काष्ठा rc_dev *dev);
पूर्ण;

काष्ठा ir_raw_event_ctrl अणु
	काष्ठा list_head		list;		/* to keep track of raw clients */
	काष्ठा task_काष्ठा		*thपढ़ो;
	/* fअगरo क्रम the pulse/space durations */
	DECLARE_KFIFO(kfअगरo, काष्ठा ir_raw_event, MAX_IR_EVENT_SIZE);
	kसमय_प्रकार				last_event;	/* when last event occurred */
	काष्ठा rc_dev			*dev;		/* poपूर्णांकer to the parent rc_dev */
	/* handle delayed ir_raw_event_store_edge processing */
	spinlock_t			edge_spinlock;
	काष्ठा समयr_list		edge_handle;

	/* raw decoder state follows */
	काष्ठा ir_raw_event prev_ev;
	काष्ठा ir_raw_event this_ev;

#अगर_घोषित CONFIG_BPF_LIRC_MODE2
	u32				bpf_sample;
	काष्ठा bpf_prog_array __rcu	*progs;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_NEC_DECODER)
	काष्ठा nec_dec अणु
		पूर्णांक state;
		अचिन्हित count;
		u32 bits;
		bool is_nec_x;
		bool necx_repeat;
	पूर्ण nec;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_RC5_DECODER)
	काष्ठा rc5_dec अणु
		पूर्णांक state;
		u32 bits;
		अचिन्हित count;
		bool is_rc5x;
	पूर्ण rc5;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_RC6_DECODER)
	काष्ठा rc6_dec अणु
		पूर्णांक state;
		u8 header;
		u32 body;
		bool toggle;
		अचिन्हित count;
		अचिन्हित wanted_bits;
	पूर्ण rc6;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_SONY_DECODER)
	काष्ठा sony_dec अणु
		पूर्णांक state;
		u32 bits;
		अचिन्हित count;
	पूर्ण sony;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_JVC_DECODER)
	काष्ठा jvc_dec अणु
		पूर्णांक state;
		u16 bits;
		u16 old_bits;
		अचिन्हित count;
		bool first;
		bool toggle;
	पूर्ण jvc;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_SANYO_DECODER)
	काष्ठा sanyo_dec अणु
		पूर्णांक state;
		अचिन्हित count;
		u64 bits;
	पूर्ण sanyo;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_SHARP_DECODER)
	काष्ठा sharp_dec अणु
		पूर्णांक state;
		अचिन्हित count;
		u32 bits;
		अचिन्हित पूर्णांक pulse_len;
	पूर्ण sharp;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_MCE_KBD_DECODER)
	काष्ठा mce_kbd_dec अणु
		/* locks key up समयr */
		spinlock_t keylock;
		काष्ठा समयr_list rx_समयout;
		पूर्णांक state;
		u8 header;
		u32 body;
		अचिन्हित count;
		अचिन्हित wanted_bits;
	पूर्ण mce_kbd;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_XMP_DECODER)
	काष्ठा xmp_dec अणु
		पूर्णांक state;
		अचिन्हित count;
		u32 durations[16];
	पूर्ण xmp;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_IMON_DECODER)
	काष्ठा imon_dec अणु
		पूर्णांक state;
		पूर्णांक count;
		पूर्णांक last_chk;
		अचिन्हित पूर्णांक bits;
		bool stick_keyboard;
	पूर्ण imon;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IR_RCMM_DECODER)
	काष्ठा rcmm_dec अणु
		पूर्णांक state;
		अचिन्हित पूर्णांक count;
		u32 bits;
	पूर्ण rcmm;
#पूर्ण_अगर
पूर्ण;

/* Mutex क्रम locking raw IR processing and handler change */
बाह्य काष्ठा mutex ir_raw_handler_lock;

/* macros क्रम IR decoders */
अटल अंतरभूत bool geq_margin(अचिन्हित d1, अचिन्हित d2, अचिन्हित margin)
अणु
	वापस d1 > (d2 - margin);
पूर्ण

अटल अंतरभूत bool eq_margin(अचिन्हित d1, अचिन्हित d2, अचिन्हित margin)
अणु
	वापस ((d1 > (d2 - margin)) && (d1 < (d2 + margin)));
पूर्ण

अटल अंतरभूत bool is_transition(काष्ठा ir_raw_event *x, काष्ठा ir_raw_event *y)
अणु
	वापस x->pulse != y->pulse;
पूर्ण

अटल अंतरभूत व्योम decrease_duration(काष्ठा ir_raw_event *ev, अचिन्हित duration)
अणु
	अगर (duration > ev->duration)
		ev->duration = 0;
	अन्यथा
		ev->duration -= duration;
पूर्ण

/* Returns true अगर event is normal pulse/space event */
अटल अंतरभूत bool is_timing_event(काष्ठा ir_raw_event ev)
अणु
	वापस !ev.carrier_report && !ev.reset;
पूर्ण

#घोषणा TO_STR(is_pulse)		((is_pulse) ? "pulse" : "space")

/* functions क्रम IR encoders */
bool rc_validate_scancode(क्रमागत rc_proto proto, u32 scancode);

अटल अंतरभूत व्योम init_ir_raw_event_duration(काष्ठा ir_raw_event *ev,
					      अचिन्हित पूर्णांक pulse,
					      u32 duration)
अणु
	*ev = (काष्ठा ir_raw_event) अणु
		.duration = duration,
		.pulse = pulse
	पूर्ण;
पूर्ण

/**
 * काष्ठा ir_raw_timings_manchester - Manchester coding timings
 * @leader_pulse:	duration of leader pulse (अगर any) 0 अगर continuing
 *			existing संकेत
 * @leader_space:	duration of leader space (अगर any)
 * @घड़ी:		duration of each pulse/space in ns
 * @invert:		अगर set घड़ी logic is inverted
 *			(0 = space + pulse, 1 = pulse + space)
 * @trailer_space:	duration of trailer space in ns
 */
काष्ठा ir_raw_timings_manchester अणु
	अचिन्हित पूर्णांक leader_pulse;
	अचिन्हित पूर्णांक leader_space;
	अचिन्हित पूर्णांक घड़ी;
	अचिन्हित पूर्णांक invert:1;
	अचिन्हित पूर्णांक trailer_space;
पूर्ण;

पूर्णांक ir_raw_gen_manchester(काष्ठा ir_raw_event **ev, अचिन्हित पूर्णांक max,
			  स्थिर काष्ठा ir_raw_timings_manchester *timings,
			  अचिन्हित पूर्णांक n, u64 data);

/**
 * ir_raw_gen_pulse_space() - generate pulse and space raw events.
 * @ev:			Poपूर्णांकer to poपूर्णांकer to next मुक्त raw event.
 *			Will be incremented क्रम each raw event written.
 * @max:		Poपूर्णांकer to number of raw events available in buffer.
 *			Will be decremented क्रम each raw event written.
 * @pulse_width:	Width of pulse in ns.
 * @space_width:	Width of space in ns.
 *
 * Returns:	0 on success.
 *		-ENOBUFS अगर there isn't enough buffer space to ग_लिखो both raw
 *		events. In this हाल @max events will have been written.
 */
अटल अंतरभूत पूर्णांक ir_raw_gen_pulse_space(काष्ठा ir_raw_event **ev,
					 अचिन्हित पूर्णांक *max,
					 अचिन्हित पूर्णांक pulse_width,
					 अचिन्हित पूर्णांक space_width)
अणु
	अगर (!*max)
		वापस -ENOBUFS;
	init_ir_raw_event_duration((*ev)++, 1, pulse_width);
	अगर (!--*max)
		वापस -ENOBUFS;
	init_ir_raw_event_duration((*ev)++, 0, space_width);
	--*max;
	वापस 0;
पूर्ण

/**
 * काष्ठा ir_raw_timings_pd - pulse-distance modulation timings
 * @header_pulse:	duration of header pulse in ns (0 क्रम none)
 * @header_space:	duration of header space in ns
 * @bit_pulse:		duration of bit pulse in ns
 * @bit_space:		duration of bit space (क्रम logic 0 and 1) in ns
 * @trailer_pulse:	duration of trailer pulse in ns
 * @trailer_space:	duration of trailer space in ns
 * @msb_first:		1 अगर most signअगरicant bit is sent first
 */
काष्ठा ir_raw_timings_pd अणु
	अचिन्हित पूर्णांक header_pulse;
	अचिन्हित पूर्णांक header_space;
	अचिन्हित पूर्णांक bit_pulse;
	अचिन्हित पूर्णांक bit_space[2];
	अचिन्हित पूर्णांक trailer_pulse;
	अचिन्हित पूर्णांक trailer_space;
	अचिन्हित पूर्णांक msb_first:1;
पूर्ण;

पूर्णांक ir_raw_gen_pd(काष्ठा ir_raw_event **ev, अचिन्हित पूर्णांक max,
		  स्थिर काष्ठा ir_raw_timings_pd *timings,
		  अचिन्हित पूर्णांक n, u64 data);

/**
 * काष्ठा ir_raw_timings_pl - pulse-length modulation timings
 * @header_pulse:	duration of header pulse in ns (0 क्रम none)
 * @bit_space:		duration of bit space in ns
 * @bit_pulse:		duration of bit pulse (क्रम logic 0 and 1) in ns
 * @trailer_space:	duration of trailer space in ns
 * @msb_first:		1 अगर most signअगरicant bit is sent first
 */
काष्ठा ir_raw_timings_pl अणु
	अचिन्हित पूर्णांक header_pulse;
	अचिन्हित पूर्णांक bit_space;
	अचिन्हित पूर्णांक bit_pulse[2];
	अचिन्हित पूर्णांक trailer_space;
	अचिन्हित पूर्णांक msb_first:1;
पूर्ण;

पूर्णांक ir_raw_gen_pl(काष्ठा ir_raw_event **ev, अचिन्हित पूर्णांक max,
		  स्थिर काष्ठा ir_raw_timings_pl *timings,
		  अचिन्हित पूर्णांक n, u64 data);

/*
 * Routines from rc-raw.c to be used पूर्णांकernally and by decoders
 */
u64 ir_raw_get_allowed_protocols(व्योम);
पूर्णांक ir_raw_event_prepare(काष्ठा rc_dev *dev);
पूर्णांक ir_raw_event_रेजिस्टर(काष्ठा rc_dev *dev);
व्योम ir_raw_event_मुक्त(काष्ठा rc_dev *dev);
व्योम ir_raw_event_unरेजिस्टर(काष्ठा rc_dev *dev);
पूर्णांक ir_raw_handler_रेजिस्टर(काष्ठा ir_raw_handler *ir_raw_handler);
व्योम ir_raw_handler_unरेजिस्टर(काष्ठा ir_raw_handler *ir_raw_handler);
व्योम ir_raw_load_modules(u64 *protocols);
व्योम ir_raw_init(व्योम);

/*
 * lirc पूर्णांकerface
 */
#अगर_घोषित CONFIG_LIRC
पूर्णांक lirc_dev_init(व्योम);
व्योम lirc_dev_निकास(व्योम);
व्योम lirc_raw_event(काष्ठा rc_dev *dev, काष्ठा ir_raw_event ev);
व्योम lirc_scancode_event(काष्ठा rc_dev *dev, काष्ठा lirc_scancode *lsc);
पूर्णांक lirc_रेजिस्टर(काष्ठा rc_dev *dev);
व्योम lirc_unरेजिस्टर(काष्ठा rc_dev *dev);
काष्ठा rc_dev *rc_dev_get_from_fd(पूर्णांक fd);
#अन्यथा
अटल अंतरभूत पूर्णांक lirc_dev_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम lirc_dev_निकास(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम lirc_raw_event(काष्ठा rc_dev *dev,
				  काष्ठा ir_raw_event ev) अणु पूर्ण
अटल अंतरभूत व्योम lirc_scancode_event(काष्ठा rc_dev *dev,
				       काष्ठा lirc_scancode *lsc) अणु पूर्ण
अटल अंतरभूत पूर्णांक lirc_रेजिस्टर(काष्ठा rc_dev *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम lirc_unरेजिस्टर(काष्ठा rc_dev *dev) अणु पूर्ण
#पूर्ण_अगर

/*
 * bpf पूर्णांकerface
 */
#अगर_घोषित CONFIG_BPF_LIRC_MODE2
व्योम lirc_bpf_मुक्त(काष्ठा rc_dev *dev);
व्योम lirc_bpf_run(काष्ठा rc_dev *dev, u32 sample);
#अन्यथा
अटल अंतरभूत व्योम lirc_bpf_मुक्त(काष्ठा rc_dev *dev) अणु पूर्ण
अटल अंतरभूत व्योम lirc_bpf_run(काष्ठा rc_dev *dev, u32 sample) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _RC_CORE_PRIV */
