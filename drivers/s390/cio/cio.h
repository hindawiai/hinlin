<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित S390_CIO_H
#घोषणा S390_CIO_H

#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <यंत्र/chpid.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/fcx.h>
#समावेश <यंत्र/schid.h>
#समावेश "chsc.h"

/*
 * path management control word
 */
काष्ठा pmcw अणु
	u32 पूर्णांकparm;		/* पूर्णांकerruption parameter */
	u32 qf	 : 1;		/* qdio facility */
	u32 w	 : 1;
	u32 isc  : 3;		/* पूर्णांकerruption sublass */
	u32 res5 : 3;		/* reserved zeros */
	u32 ena  : 1;		/* enabled */
	u32 lm	 : 2;		/* limit mode */
	u32 mme  : 2;		/* measurement-mode enable */
	u32 mp	 : 1;		/* multipath mode */
	u32 tf	 : 1;		/* timing facility */
	u32 dnv  : 1;		/* device number valid */
	u32 dev  : 16;		/* device number */
	u8  lpm;		/* logical path mask */
	u8  pnom;		/* path not operational mask */
	u8  lpum;		/* last path used mask */
	u8  pim;		/* path installed mask */
	u16 mbi;		/* measurement-block index */
	u8  pom;		/* path operational mask */
	u8  pam;		/* path available mask */
	u8  chpid[8];		/* CHPID 0-7 (अगर available) */
	u32 unused1 : 8;	/* reserved zeros */
	u32 st	    : 3;	/* subchannel type */
	u32 unused2 : 18;	/* reserved zeros */
	u32 mbfc    : 1;	/* measurement block क्रमmat control */
	u32 xmwme   : 1;	/* extended measurement word mode enable */
	u32 csense  : 1;	/* concurrent sense; can be enabled ...*/
				/*  ... per MSCH, however, अगर facility */
				/*  ... is not installed, this results */
				/*  ... in an opeअक्रम exception.       */
पूर्ण __attribute__ ((packed));

/* I/O-Interruption Code as stored by TEST PENDING INTERRUPTION (TPI). */
काष्ठा tpi_info अणु
	काष्ठा subchannel_id schid;
	u32 पूर्णांकparm;
	u32 adapter_IO:1;
	u32 directed_irq:1;
	u32 isc:3;
	u32 :27;
	u32 type:3;
	u32 :12;
पूर्ण __packed __aligned(4);

/* Target SCHIB configuration. */
काष्ठा schib_config अणु
	u64 mba;
	u32 पूर्णांकparm;
	u16 mbi;
	u32 isc:3;
	u32 ena:1;
	u32 mme:2;
	u32 mp:1;
	u32 csense:1;
	u32 mbfc:1;
पूर्ण __attribute__ ((packed));

/*
 * subchannel inक्रमmation block
 */
काष्ठा schib अणु
	काष्ठा pmcw pmcw;	 /* path management control word */
	जोड़ scsw scsw;	 /* subchannel status word */
	__u64 mba;               /* measurement block address */
	__u8 mda[4];		 /* model dependent area */
पूर्ण __attribute__ ((packed,aligned(4)));

/*
 * When rescheduled, toकरो's with higher values will overग_लिखो those
 * with lower values.
 */
क्रमागत sch_toकरो अणु
	SCH_TODO_NOTHING,
	SCH_TODO_EVAL,
	SCH_TODO_UNREG,
पूर्ण;

/* subchannel data काष्ठाure used by I/O subroutines */
काष्ठा subchannel अणु
	काष्ठा subchannel_id schid;
	spinlock_t *lock;	/* subchannel lock */
	काष्ठा mutex reg_mutex;
	क्रमागत अणु
		SUBCHANNEL_TYPE_IO = 0,
		SUBCHANNEL_TYPE_CHSC = 1,
		SUBCHANNEL_TYPE_MSG = 2,
		SUBCHANNEL_TYPE_ADM = 3,
	पूर्ण st;			/* subchannel type */
	__u8 vpm;		/* verअगरied path mask */
	__u8 lpm;		/* logical path mask */
	__u8 opm;               /* operational path mask */
	काष्ठा schib schib;	/* subchannel inक्रमmation block */
	पूर्णांक isc; /* desired पूर्णांकerruption subclass */
	काष्ठा chsc_ssd_info ssd_info;	/* subchannel description */
	काष्ठा device dev;	/* entry in device tree */
	काष्ठा css_driver *driver;
	क्रमागत sch_toकरो toकरो;
	काष्ठा work_काष्ठा toकरो_work;
	काष्ठा schib_config config;
	u64 dma_mask;
	अक्षर *driver_override; /* Driver name to क्रमce a match */
पूर्ण __attribute__ ((aligned(8)));

DECLARE_PER_CPU_ALIGNED(काष्ठा irb, cio_irb);

#घोषणा to_subchannel(n) container_of(n, काष्ठा subchannel, dev)

बाह्य पूर्णांक cio_enable_subchannel(काष्ठा subchannel *, u32);
बाह्य पूर्णांक cio_disable_subchannel (काष्ठा subchannel *);
बाह्य पूर्णांक cio_cancel (काष्ठा subchannel *);
बाह्य पूर्णांक cio_clear (काष्ठा subchannel *);
बाह्य पूर्णांक cio_cancel_halt_clear(काष्ठा subchannel *, पूर्णांक *);
बाह्य पूर्णांक cio_resume (काष्ठा subchannel *);
बाह्य पूर्णांक cio_halt (काष्ठा subchannel *);
बाह्य पूर्णांक cio_start (काष्ठा subchannel *, काष्ठा ccw1 *, __u8);
बाह्य पूर्णांक cio_start_key (काष्ठा subchannel *, काष्ठा ccw1 *, __u8, __u8);
बाह्य पूर्णांक cio_set_options (काष्ठा subchannel *, पूर्णांक);
बाह्य पूर्णांक cio_update_schib(काष्ठा subchannel *sch);
बाह्य पूर्णांक cio_commit_config(काष्ठा subchannel *sch);

पूर्णांक cio_पंचांग_start_key(काष्ठा subchannel *sch, काष्ठा tcw *tcw, u8 lpm, u8 key);
पूर्णांक cio_पंचांग_पूर्णांकrg(काष्ठा subchannel *sch);

बाह्य पूर्णांक __init airq_init(व्योम);

/* Use with care. */
#अगर_घोषित CONFIG_CCW_CONSOLE
बाह्य काष्ठा subchannel *cio_probe_console(व्योम);
बाह्य पूर्णांक cio_is_console(काष्ठा subchannel_id);
बाह्य व्योम cio_रेजिस्टर_early_subchannels(व्योम);
बाह्य व्योम cio_tsch(काष्ठा subchannel *sch);
#अन्यथा
#घोषणा cio_is_console(schid) 0
अटल अंतरभूत व्योम cio_रेजिस्टर_early_subchannels(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
