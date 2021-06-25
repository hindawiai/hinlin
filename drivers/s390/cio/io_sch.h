<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित S390_IO_SCH_H
#घोषणा S390_IO_SCH_H

#समावेश <linux/types.h>
#समावेश <यंत्र/schid.h>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/irq.h>
#समावेश "css.h"
#समावेश "orb.h"

काष्ठा io_subchannel_dma_area अणु
	काष्ठा ccw1 sense_ccw;	/* अटल ccw क्रम sense command */
पूर्ण;

काष्ठा io_subchannel_निजी अणु
	जोड़ orb orb;		/* operation request block */
	काष्ठा ccw_device *cdev;/* poपूर्णांकer to the child ccw device */
	काष्ठा अणु
		अचिन्हित पूर्णांक suspend:1;	/* allow suspend */
		अचिन्हित पूर्णांक prefetch:1;/* deny prefetch */
		अचिन्हित पूर्णांक पूर्णांकer:1;	/* suppress पूर्णांकermediate पूर्णांकerrupts */
	पूर्ण __packed options;
	काष्ठा io_subchannel_dma_area *dma_area;
	dma_addr_t dma_area_dma;
पूर्ण __aligned(8);

#घोषणा to_io_निजी(n) ((काष्ठा io_subchannel_निजी *) \
			  dev_get_drvdata(&(n)->dev))
#घोषणा set_io_निजी(n, p) (dev_set_drvdata(&(n)->dev, p))

अटल अंतरभूत काष्ठा ccw_device *sch_get_cdev(काष्ठा subchannel *sch)
अणु
	काष्ठा io_subchannel_निजी *priv = to_io_निजी(sch);
	वापस priv ? priv->cdev : शून्य;
पूर्ण

अटल अंतरभूत व्योम sch_set_cdev(काष्ठा subchannel *sch,
				काष्ठा ccw_device *cdev)
अणु
	काष्ठा io_subchannel_निजी *priv = to_io_निजी(sch);
	अगर (priv)
		priv->cdev = cdev;
पूर्ण

#घोषणा MAX_CIWS 8

/*
 * Possible status values क्रम a CCW request's I/O.
 */
क्रमागत io_status अणु
	IO_DONE,
	IO_RUNNING,
	IO_STATUS_ERROR,
	IO_PATH_ERROR,
	IO_REJECTED,
	IO_KILLED
पूर्ण;

/**
 * ccw_request - Internal CCW request.
 * @cp: channel program to start
 * @समयout: maximum allowable समय in jअगरfies between start I/O and पूर्णांकerrupt
 * @maxretries: number of retries per I/O operation and path
 * @lpm: mask of paths to use
 * @check: optional callback that determines अगर results are final
 * @filter: optional callback to adjust request status based on IRB data
 * @callback: final callback
 * @data: user-defined poपूर्णांकer passed to all callbacks
 * @singlepath: अगर set, use only one path from @lpm per start I/O
 * @cancel: non-zero अगर request was cancelled
 * @करोne: non-zero अगर request was finished
 * @mask: current path mask
 * @retries: current number of retries
 * @drc: delayed वापस code
 */
काष्ठा ccw_request अणु
	काष्ठा ccw1 *cp;
	अचिन्हित दीर्घ समयout;
	u16 maxretries;
	u8 lpm;
	पूर्णांक (*check)(काष्ठा ccw_device *, व्योम *);
	क्रमागत io_status (*filter)(काष्ठा ccw_device *, व्योम *, काष्ठा irb *,
				 क्रमागत io_status);
	व्योम (*callback)(काष्ठा ccw_device *, व्योम *, पूर्णांक);
	व्योम *data;
	अचिन्हित पूर्णांक singlepath:1;
	/* These fields are used पूर्णांकernally. */
	अचिन्हित पूर्णांक cancel:1;
	अचिन्हित पूर्णांक करोne:1;
	u16 mask;
	u16 retries;
	पूर्णांक drc;
पूर्ण __attribute__((packed));

/*
 * sense-id response buffer layout
 */
काष्ठा senseid अणु
	/* common part */
	u8  reserved;	/* always 0x'FF' */
	u16 cu_type;	/* control unit type */
	u8  cu_model;	/* control unit model */
	u16 dev_type;	/* device type */
	u8  dev_model;	/* device model */
	u8  unused;	/* padding byte */
	/* extended part */
	काष्ठा ciw ciw[MAX_CIWS];	/* variable # of CIWs */
पूर्ण  __attribute__ ((packed, aligned(4)));

क्रमागत cdev_toकरो अणु
	CDEV_TODO_NOTHING,
	CDEV_TODO_ENABLE_CMF,
	CDEV_TODO_REBIND,
	CDEV_TODO_REGISTER,
	CDEV_TODO_UNREG,
	CDEV_TODO_UNREG_EVAL,
पूर्ण;

#घोषणा FAKE_CMD_IRB	1
#घोषणा FAKE_TM_IRB	2

काष्ठा ccw_device_dma_area अणु
	काष्ठा senseid senseid;	/* SenseID info */
	काष्ठा ccw1 iccws[2];	/* ccws क्रम SNID/SID/SPGID commands */
	काष्ठा irb irb;		/* device status */
	काष्ठा pgid pgid[8];	/* path group IDs per chpid*/
पूर्ण;

काष्ठा ccw_device_निजी अणु
	काष्ठा ccw_device *cdev;
	काष्ठा subchannel *sch;
	पूर्णांक state;		/* device state */
	atomic_t onoff;
	काष्ठा ccw_dev_id dev_id;	/* device id */
	काष्ठा ccw_request req;		/* पूर्णांकernal I/O request */
	पूर्णांक iretry;
	u8 pgid_valid_mask;	/* mask of valid PGIDs */
	u8 pgid_toकरो_mask;	/* mask of PGIDs to be adjusted */
	u8 pgid_reset_mask;	/* mask of PGIDs which were reset */
	u8 path_noirq_mask;	/* mask of paths क्रम which no irq was
				   received */
	u8 path_notoper_mask;	/* mask of paths which were found
				   not operable */
	u8 path_gone_mask;	/* mask of paths, that became unavailable */
	u8 path_new_mask;	/* mask of paths, that became available */
	u8 path_broken_mask;	/* mask of paths, which were found to be
				   unusable */
	काष्ठा अणु
		अचिन्हित पूर्णांक fast:1;	/* post with "channel end" */
		अचिन्हित पूर्णांक repall:1;	/* report every पूर्णांकerrupt status */
		अचिन्हित पूर्णांक pgroup:1;	/* करो path grouping */
		अचिन्हित पूर्णांक क्रमce:1;	/* allow क्रमced online */
		अचिन्हित पूर्णांक mpath:1;	/* करो multipathing */
	पूर्ण __attribute__ ((packed)) options;
	काष्ठा अणु
		अचिन्हित पूर्णांक esid:1;	    /* Ext. SenseID supported by HW */
		अचिन्हित पूर्णांक करोsense:1;	    /* delayed SENSE required */
		अचिन्हित पूर्णांक करोverअगरy:1;    /* delayed path verअगरication */
		अचिन्हित पूर्णांक करोnotअगरy:1;    /* call notअगरy function */
		अचिन्हित पूर्णांक recog_करोne:1;  /* dev. recog. complete */
		अचिन्हित पूर्णांक fake_irb:2;    /* deliver faked irb */
		अचिन्हित पूर्णांक pgroup:1;	    /* pathgroup is set up */
		अचिन्हित पूर्णांक mpath:1;	    /* multipathing is set up */
		अचिन्हित पूर्णांक pgid_unknown:1;/* unknown pgid state */
		अचिन्हित पूर्णांक initialized:1; /* set अगर initial reference held */
	पूर्ण __attribute__((packed)) flags;
	अचिन्हित दीर्घ पूर्णांकparm;	/* user पूर्णांकerruption parameter */
	काष्ठा qdio_irq *qdio_data;
	पूर्णांक async_समाप्त_io_rc;
	काष्ठा work_काष्ठा toकरो_work;
	क्रमागत cdev_toकरो toकरो;
	रुको_queue_head_t रुको_q;
	काष्ठा समयr_list समयr;
	व्योम *cmb;			/* measurement inक्रमmation */
	काष्ठा list_head cmb_list;	/* list of measured devices */
	u64 cmb_start_समय;		/* घड़ी value of cmb reset */
	व्योम *cmb_रुको;			/* deferred cmb enable/disable */
	काष्ठा gen_pool *dma_pool;
	काष्ठा ccw_device_dma_area *dma_area;
	क्रमागत पूर्णांकerruption_class पूर्णांक_class;
पूर्ण;

#पूर्ण_अगर
