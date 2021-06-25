<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * NVMe over Fabrics common host code.
 * Copyright (c) 2015-2016 HGST, a Western Digital Company.
 */
#अगर_अघोषित _NVME_FABRICS_H
#घोषणा _NVME_FABRICS_H 1

#समावेश <linux/in.h>
#समावेश <linux/inet.h>

#घोषणा NVMF_MIN_QUEUE_SIZE	16
#घोषणा NVMF_MAX_QUEUE_SIZE	1024
#घोषणा NVMF_DEF_QUEUE_SIZE	128
#घोषणा NVMF_DEF_RECONNECT_DELAY	10
/* शेष to 600 seconds of reconnect attempts beक्रमe giving up */
#घोषणा NVMF_DEF_CTRL_LOSS_TMO		600
/* शेष is -1: the fail fast mechanism is disabled  */
#घोषणा NVMF_DEF_FAIL_FAST_TMO		-1

/*
 * Reserved one command क्रम पूर्णांकernal usage.  This command is used क्रम sending
 * the connect command, as well as क्रम the keep alive command on the admin
 * queue once live.
 */
#घोषणा NVMF_RESERVED_TAGS	1

/*
 * Define a host as seen by the target.  We allocate one at boot, but also
 * allow the override it when creating controllers.  This is both to provide
 * persistence of the Host NQN over multiple boots, and to allow using
 * multiple ones, क्रम example in a container scenario.  Because we must not
 * use dअगरferent Host NQNs with the same Host ID we generate a Host ID and
 * use this काष्ठाure to keep track of the relation between the two.
 */
काष्ठा nvmf_host अणु
	काष्ठा kref		ref;
	काष्ठा list_head	list;
	अक्षर			nqn[NVMF_NQN_SIZE];
	uuid_t			id;
पूर्ण;

/**
 * क्रमागत nvmf_parsing_opts - used to define the sysfs parsing options used.
 */
क्रमागत अणु
	NVMF_OPT_ERR		= 0,
	NVMF_OPT_TRANSPORT	= 1 << 0,
	NVMF_OPT_NQN		= 1 << 1,
	NVMF_OPT_TRADDR		= 1 << 2,
	NVMF_OPT_TRSVCID	= 1 << 3,
	NVMF_OPT_QUEUE_SIZE	= 1 << 4,
	NVMF_OPT_NR_IO_QUEUES	= 1 << 5,
	NVMF_OPT_TL_RETRY_COUNT	= 1 << 6,
	NVMF_OPT_KATO		= 1 << 7,
	NVMF_OPT_HOSTNQN	= 1 << 8,
	NVMF_OPT_RECONNECT_DELAY = 1 << 9,
	NVMF_OPT_HOST_TRADDR	= 1 << 10,
	NVMF_OPT_CTRL_LOSS_TMO	= 1 << 11,
	NVMF_OPT_HOST_ID	= 1 << 12,
	NVMF_OPT_DUP_CONNECT	= 1 << 13,
	NVMF_OPT_DISABLE_SQFLOW = 1 << 14,
	NVMF_OPT_HDR_DIGEST	= 1 << 15,
	NVMF_OPT_DATA_DIGEST	= 1 << 16,
	NVMF_OPT_NR_WRITE_QUEUES = 1 << 17,
	NVMF_OPT_NR_POLL_QUEUES = 1 << 18,
	NVMF_OPT_TOS		= 1 << 19,
	NVMF_OPT_FAIL_FAST_TMO	= 1 << 20,
पूर्ण;

/**
 * काष्ठा nvmf_ctrl_options - Used to hold the options specअगरied
 *			      with the parsing opts क्रमागत.
 * @mask:	Used by the fabrics library to parse through sysfs options
 *		on adding a NVMe controller.
 * @transport:	Holds the fabric transport "technology name" (क्रम a lack of
 *		better description) that will be used by an NVMe controller
 *		being added.
 * @subsysnqn:	Hold the fully qualअगरied NQN subystem name (क्रमmat defined
 *		in the NVMe specअगरication, "NVMe Qualified Names").
 * @traddr:	The transport-specअगरic TRADDR field क्रम a port on the
 *              subप्रणाली which is adding a controller.
 * @trsvcid:	The transport-specअगरic TRSVCID field क्रम a port on the
 *              subप्रणाली which is adding a controller.
 * @host_traddr: A transport-specअगरic field identअगरying the NVME host port
 *              to use क्रम the connection to the controller.
 * @queue_size: Number of IO queue elements.
 * @nr_io_queues: Number of controller IO queues that will be established.
 * @reconnect_delay: Time between two consecutive reconnect attempts.
 * @discovery_nqn: indicates अगर the subsysnqn is the well-known discovery NQN.
 * @kato:	Keep-alive समयout.
 * @host:	Virtual NVMe host, contains the NQN and Host ID.
 * @max_reconnects: maximum number of allowed reconnect attempts beक्रमe removing
 *              the controller, (-1) means reconnect क्रमever, zero means हटाओ
 *              immediately;
 * @disable_sqflow: disable controller sq flow control
 * @hdr_digest: generate/verअगरy header digest (TCP)
 * @data_digest: generate/verअगरy data digest (TCP)
 * @nr_ग_लिखो_queues: number of queues क्रम ग_लिखो I/O
 * @nr_poll_queues: number of queues क्रम polling I/O
 * @tos: type of service
 * @fast_io_fail_पंचांगo: Fast I/O fail समयout in seconds
 */
काष्ठा nvmf_ctrl_options अणु
	अचिन्हित		mask;
	अक्षर			*transport;
	अक्षर			*subsysnqn;
	अक्षर			*traddr;
	अक्षर			*trsvcid;
	अक्षर			*host_traddr;
	माप_प्रकार			queue_size;
	अचिन्हित पूर्णांक		nr_io_queues;
	अचिन्हित पूर्णांक		reconnect_delay;
	bool			discovery_nqn;
	bool			duplicate_connect;
	अचिन्हित पूर्णांक		kato;
	काष्ठा nvmf_host	*host;
	पूर्णांक			max_reconnects;
	bool			disable_sqflow;
	bool			hdr_digest;
	bool			data_digest;
	अचिन्हित पूर्णांक		nr_ग_लिखो_queues;
	अचिन्हित पूर्णांक		nr_poll_queues;
	पूर्णांक			tos;
	पूर्णांक			fast_io_fail_पंचांगo;
पूर्ण;

/*
 * काष्ठा nvmf_transport_ops - used to रेजिस्टर a specअगरic
 *			       fabric implementation of NVMe fabrics.
 * @entry:		Used by the fabrics library to add the new
 *			registration entry to its linked-list पूर्णांकernal tree.
 * @module:             Transport module reference
 * @name:		Name of the NVMe fabric driver implementation.
 * @required_opts:	sysfs command-line options that must be specअगरied
 *			when adding a new NVMe controller.
 * @allowed_opts:	sysfs command-line options that can be specअगरied
 *			when adding a new NVMe controller.
 * @create_ctrl():	function poपूर्णांकer that poपूर्णांकs to a non-NVMe
 *			implementation-specअगरic fabric technology
 *			that would go पूर्णांकo starting up that fabric
 *			क्रम the purpose of conneciton to an NVMe controller
 *			using that fabric technology.
 *
 * Notes:
 *	1. At minimum, 'required_opts' and 'allowed_opts' should
 *	   be set to the same क्रमागत parsing options defined earlier.
 *	2. create_ctrl() must be defined (even अगर it करोes nothing)
 *	3. काष्ठा nvmf_transport_ops must be अटलally allocated in the
 *	   modules .bss section so that a pure module_get on @module
 *	   prevents the memory from beeing मुक्तd.
 */
काष्ठा nvmf_transport_ops अणु
	काष्ठा list_head	entry;
	काष्ठा module		*module;
	स्थिर अक्षर		*name;
	पूर्णांक			required_opts;
	पूर्णांक			allowed_opts;
	काष्ठा nvme_ctrl	*(*create_ctrl)(काष्ठा device *dev,
					काष्ठा nvmf_ctrl_options *opts);
पूर्ण;

अटल अंतरभूत bool
nvmf_ctlr_matches_baseopts(काष्ठा nvme_ctrl *ctrl,
			काष्ठा nvmf_ctrl_options *opts)
अणु
	अगर (ctrl->state == NVME_CTRL_DELETING ||
	    ctrl->state == NVME_CTRL_DEAD ||
	    म_भेद(opts->subsysnqn, ctrl->opts->subsysnqn) ||
	    म_भेद(opts->host->nqn, ctrl->opts->host->nqn) ||
	    स_भेद(&opts->host->id, &ctrl->opts->host->id, माप(uuid_t)))
		वापस false;

	वापस true;
पूर्ण

पूर्णांक nvmf_reg_पढ़ो32(काष्ठा nvme_ctrl *ctrl, u32 off, u32 *val);
पूर्णांक nvmf_reg_पढ़ो64(काष्ठा nvme_ctrl *ctrl, u32 off, u64 *val);
पूर्णांक nvmf_reg_ग_लिखो32(काष्ठा nvme_ctrl *ctrl, u32 off, u32 val);
पूर्णांक nvmf_connect_admin_queue(काष्ठा nvme_ctrl *ctrl);
पूर्णांक nvmf_connect_io_queue(काष्ठा nvme_ctrl *ctrl, u16 qid, bool poll);
पूर्णांक nvmf_रेजिस्टर_transport(काष्ठा nvmf_transport_ops *ops);
व्योम nvmf_unरेजिस्टर_transport(काष्ठा nvmf_transport_ops *ops);
व्योम nvmf_मुक्त_options(काष्ठा nvmf_ctrl_options *opts);
पूर्णांक nvmf_get_address(काष्ठा nvme_ctrl *ctrl, अक्षर *buf, पूर्णांक size);
bool nvmf_should_reconnect(काष्ठा nvme_ctrl *ctrl);
bool nvmf_ip_options_match(काष्ठा nvme_ctrl *ctrl,
		काष्ठा nvmf_ctrl_options *opts);

#पूर्ण_अगर /* _NVME_FABRICS_H */
