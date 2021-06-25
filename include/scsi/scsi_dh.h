<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Header file क्रम SCSI device handler infraकाष्ठाure.
 *
 * Modअगरied version of patches posted by Mike Christie <michaelc@cs.wisc.edu>
 *
 * Copyright IBM Corporation, 2007
 *      Authors:
 *               Chandra Seetharaman <sekharan@us.ibm.com>
 *               Mike Anderson <andmike@linux.vnet.ibm.com>
 */

#समावेश <scsi/scsi_device.h>

क्रमागत अणु
	SCSI_DH_OK = 0,
	/*
	 * device errors
	 */
	SCSI_DH_DEV_FAILED,	/* generic device error */
	SCSI_DH_DEV_TEMP_BUSY,
	SCSI_DH_DEV_UNSUPP,	/* device handler not supported */
	SCSI_DH_DEVICE_MAX,	/* max device blkerr definition */

	/*
	 * transport errors
	 */
	SCSI_DH_NOTCONN = SCSI_DH_DEVICE_MAX + 1,
	SCSI_DH_CONN_FAILURE,
	SCSI_DH_TRANSPORT_MAX,	/* max transport blkerr definition */

	/*
	 * driver and generic errors
	 */
	SCSI_DH_IO = SCSI_DH_TRANSPORT_MAX + 1,	/* generic error */
	SCSI_DH_INVALID_IO,
	SCSI_DH_RETRY,		/* retry the req, but not immediately */
	SCSI_DH_IMM_RETRY,	/* immediately retry the req */
	SCSI_DH_TIMED_OUT,
	SCSI_DH_RES_TEMP_UNAVAIL,
	SCSI_DH_DEV_OFFLINED,
	SCSI_DH_NOMEM,
	SCSI_DH_NOSYS,
	SCSI_DH_DRIVER_MAX,
पूर्ण;

प्रकार व्योम (*activate_complete)(व्योम *, पूर्णांक);
काष्ठा scsi_device_handler अणु
	/* Used by the infraकाष्ठाure */
	काष्ठा list_head list; /* list of scsi_device_handlers */

	/* Filled by the hardware handler */
	काष्ठा module *module;
	स्थिर अक्षर *name;
	क्रमागत scsi_disposition (*check_sense)(काष्ठा scsi_device *,
					     काष्ठा scsi_sense_hdr *);
	पूर्णांक (*attach)(काष्ठा scsi_device *);
	व्योम (*detach)(काष्ठा scsi_device *);
	पूर्णांक (*activate)(काष्ठा scsi_device *, activate_complete, व्योम *);
	blk_status_t (*prep_fn)(काष्ठा scsi_device *, काष्ठा request *);
	पूर्णांक (*set_params)(काष्ठा scsi_device *, स्थिर अक्षर *);
	व्योम (*rescan)(काष्ठा scsi_device *);
पूर्ण;

#अगर_घोषित CONFIG_SCSI_DH
बाह्य पूर्णांक scsi_dh_activate(काष्ठा request_queue *, activate_complete, व्योम *);
बाह्य पूर्णांक scsi_dh_attach(काष्ठा request_queue *, स्थिर अक्षर *);
बाह्य स्थिर अक्षर *scsi_dh_attached_handler_name(काष्ठा request_queue *, gfp_t);
बाह्य पूर्णांक scsi_dh_set_params(काष्ठा request_queue *, स्थिर अक्षर *);
#अन्यथा
अटल अंतरभूत पूर्णांक scsi_dh_activate(काष्ठा request_queue *req,
					activate_complete fn, व्योम *data)
अणु
	fn(data, 0);
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक scsi_dh_attach(काष्ठा request_queue *req, स्थिर अक्षर *name)
अणु
	वापस SCSI_DH_NOSYS;
पूर्ण
अटल अंतरभूत स्थिर अक्षर *scsi_dh_attached_handler_name(काष्ठा request_queue *q,
							gfp_t gfp)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत पूर्णांक scsi_dh_set_params(काष्ठा request_queue *req, स्थिर अक्षर *params)
अणु
	वापस -SCSI_DH_NOSYS;
पूर्ण
#पूर्ण_अगर
