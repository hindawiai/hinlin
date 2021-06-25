<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SCSI_TRANSPORT_SRP_H
#घोषणा SCSI_TRANSPORT_SRP_H

#समावेश <linux/transport_class.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>

#घोषणा SRP_RPORT_ROLE_INITIATOR 0
#घोषणा SRP_RPORT_ROLE_TARGET 1

काष्ठा srp_rport_identअगरiers अणु
	u8 port_id[16];
	u8 roles;
पूर्ण;

/**
 * क्रमागत srp_rport_state - SRP transport layer state
 * @SRP_RPORT_RUNNING:   Transport layer operational.
 * @SRP_RPORT_BLOCKED:   Transport layer not operational; fast I/O fail समयr
 *                       is running and I/O has been blocked.
 * @SRP_RPORT_FAIL_FAST: Fast I/O fail समयr has expired; fail I/O fast.
 * @SRP_RPORT_LOST:      Port is being हटाओd.
 */
क्रमागत srp_rport_state अणु
	SRP_RPORT_RUNNING,
	SRP_RPORT_BLOCKED,
	SRP_RPORT_FAIL_FAST,
	SRP_RPORT_LOST,
पूर्ण;

/**
 * काष्ठा srp_rport - SRP initiator or target port
 *
 * Fields that are relevant क्रम SRP initiator and SRP target drivers:
 * @dev:               Device associated with this rport.
 * @port_id:           16-byte port identअगरier.
 * @roles:             Role of this port - initiator or target.
 *
 * Fields that are only relevant क्रम SRP initiator drivers:
 * @lld_data:          LLD निजी data.
 * @mutex:             Protects against concurrent rport reconnect /
 *                     fast_io_fail / dev_loss_पंचांगo activity.
 * @state:             rport state.
 * @reconnect_delay:   Reconnect delay in seconds.
 * @failed_reconnects: Number of failed reconnect attempts.
 * @reconnect_work:    Work काष्ठाure used क्रम scheduling reconnect attempts.
 * @fast_io_fail_पंचांगo:  Fast I/O fail समयout in seconds.
 * @dev_loss_पंचांगo:      Device loss समयout in seconds.
 * @fast_io_fail_work: Work काष्ठाure used क्रम scheduling fast I/O fail work.
 * @dev_loss_work:     Work काष्ठाure used क्रम scheduling device loss work.
 */
काष्ठा srp_rport अणु
	/* क्रम initiator and target drivers */

	काष्ठा device dev;

	u8 port_id[16];
	u8 roles;

	/* क्रम initiator drivers */

	व्योम			*lld_data;

	काष्ठा mutex		mutex;
	क्रमागत srp_rport_state	state;
	पूर्णांक			reconnect_delay;
	पूर्णांक			failed_reconnects;
	काष्ठा delayed_work	reconnect_work;
	पूर्णांक			fast_io_fail_पंचांगo;
	पूर्णांक			dev_loss_पंचांगo;
	काष्ठा delayed_work	fast_io_fail_work;
	काष्ठा delayed_work	dev_loss_work;
पूर्ण;

/**
 * काष्ठा srp_function_ढाँचा
 *
 * Fields that are only relevant क्रम SRP initiator drivers:
 * @has_rport_state: Whether or not to create the state, fast_io_fail_पंचांगo and
 *     dev_loss_पंचांगo sysfs attribute क्रम an rport.
 * @reset_समयr_अगर_blocked: Whether or srp_समयd_out() should reset the command
 *     समयr अगर the device on which it has been queued is blocked.
 * @reconnect_delay: If not शून्य, poपूर्णांकs to the शेष reconnect_delay value.
 * @fast_io_fail_पंचांगo: If not शून्य, poपूर्णांकs to the शेष fast_io_fail_पंचांगo value.
 * @dev_loss_पंचांगo: If not शून्य, poपूर्णांकs to the शेष dev_loss_पंचांगo value.
 * @reconnect: Callback function क्रम reconnecting to the target. See also
 *     srp_reconnect_rport().
 * @terminate_rport_io: Callback function क्रम terminating all outstanding I/O
 *     requests क्रम an rport.
 * @rport_delete: Callback function that deletes an rport.
 */
काष्ठा srp_function_ढाँचा अणु
	/* क्रम initiator drivers */
	bool has_rport_state;
	bool reset_समयr_अगर_blocked;
	पूर्णांक *reconnect_delay;
	पूर्णांक *fast_io_fail_पंचांगo;
	पूर्णांक *dev_loss_पंचांगo;
	पूर्णांक (*reconnect)(काष्ठा srp_rport *rport);
	व्योम (*terminate_rport_io)(काष्ठा srp_rport *rport);
	व्योम (*rport_delete)(काष्ठा srp_rport *rport);
पूर्ण;

बाह्य काष्ठा scsi_transport_ढाँचा *
srp_attach_transport(काष्ठा srp_function_ढाँचा *);
बाह्य व्योम srp_release_transport(काष्ठा scsi_transport_ढाँचा *);

बाह्य व्योम srp_rport_get(काष्ठा srp_rport *rport);
बाह्य व्योम srp_rport_put(काष्ठा srp_rport *rport);
बाह्य काष्ठा srp_rport *srp_rport_add(काष्ठा Scsi_Host *,
				       काष्ठा srp_rport_identअगरiers *);
बाह्य व्योम srp_rport_del(काष्ठा srp_rport *);
बाह्य पूर्णांक srp_पंचांगo_valid(पूर्णांक reconnect_delay, पूर्णांक fast_io_fail_पंचांगo,
			 दीर्घ dev_loss_पंचांगo);
पूर्णांक srp_parse_पंचांगo(पूर्णांक *पंचांगo, स्थिर अक्षर *buf);
बाह्य पूर्णांक srp_reconnect_rport(काष्ठा srp_rport *rport);
बाह्य व्योम srp_start_tl_fail_समयrs(काष्ठा srp_rport *rport);
बाह्य व्योम srp_हटाओ_host(काष्ठा Scsi_Host *);
बाह्य व्योम srp_stop_rport_समयrs(काष्ठा srp_rport *rport);
क्रमागत blk_eh_समयr_वापस srp_समयd_out(काष्ठा scsi_cmnd *scmd);

/**
 * srp_chkपढ़ोy() - evaluate the transport layer state beक्रमe I/O
 * @rport: SRP target port poपूर्णांकer.
 *
 * Returns a SCSI result code that can be वापसed by the LLD queuecommand()
 * implementation. The role of this function is similar to that of
 * fc_remote_port_chkपढ़ोy().
 */
अटल अंतरभूत पूर्णांक srp_chkपढ़ोy(काष्ठा srp_rport *rport)
अणु
	चयन (rport->state) अणु
	हाल SRP_RPORT_RUNNING:
	हाल SRP_RPORT_BLOCKED:
	शेष:
		वापस 0;
	हाल SRP_RPORT_FAIL_FAST:
		वापस DID_TRANSPORT_FAILFAST << 16;
	हाल SRP_RPORT_LOST:
		वापस DID_NO_CONNECT << 16;
	पूर्ण
पूर्ण

#पूर्ण_अगर
