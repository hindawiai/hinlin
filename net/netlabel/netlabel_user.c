<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NetLabel NETLINK Interface
 *
 * This file defines the NETLINK पूर्णांकerface क्रम the NetLabel प्रणाली.  The
 * NetLabel प्रणाली manages अटल and dynamic label mappings क्रम network
 * protocols such as CIPSO and RIPSO.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006
 */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/socket.h>
#समावेश <linux/audit.h>
#समावेश <linux/tty.h>
#समावेश <linux/security.h>
#समावेश <linux/gfp.h>
#समावेश <net/sock.h>
#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>
#समावेश <net/netlabel.h>
#समावेश <यंत्र/bug.h>

#समावेश "netlabel_mgmt.h"
#समावेश "netlabel_unlabeled.h"
#समावेश "netlabel_cipso_v4.h"
#समावेश "netlabel_calipso.h"
#समावेश "netlabel_user.h"

/*
 * NetLabel NETLINK Setup Functions
 */

/**
 * netlbl_netlink_init - Initialize the NETLINK communication channel
 *
 * Description:
 * Call out to the NetLabel components so they can रेजिस्टर their families and
 * commands with the Generic NETLINK mechanism.  Returns zero on success and
 * non-zero on failure.
 *
 */
पूर्णांक __init netlbl_netlink_init(व्योम)
अणु
	पूर्णांक ret_val;

	ret_val = netlbl_mgmt_genl_init();
	अगर (ret_val != 0)
		वापस ret_val;

	ret_val = netlbl_cipsov4_genl_init();
	अगर (ret_val != 0)
		वापस ret_val;

	ret_val = netlbl_calipso_genl_init();
	अगर (ret_val != 0)
		वापस ret_val;

	वापस netlbl_unlabel_genl_init();
पूर्ण

/*
 * NetLabel Audit Functions
 */

/**
 * netlbl_audit_start_common - Start an audit message
 * @type: audit message type
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Start an audit message using the type specअगरied in @type and fill the audit
 * message with some fields common to all NetLabel audit messages.  Returns
 * a poपूर्णांकer to the audit buffer on success, शून्य on failure.
 *
 */
काष्ठा audit_buffer *netlbl_audit_start_common(पूर्णांक type,
					       काष्ठा netlbl_audit *audit_info)
अणु
	काष्ठा audit_buffer *audit_buf;
	अक्षर *secctx;
	u32 secctx_len;

	अगर (audit_enabled == AUDIT_OFF)
		वापस शून्य;

	audit_buf = audit_log_start(audit_context(), GFP_ATOMIC, type);
	अगर (audit_buf == शून्य)
		वापस शून्य;

	audit_log_क्रमmat(audit_buf, "netlabel: auid=%u ses=%u",
			 from_kuid(&init_user_ns, audit_info->loginuid),
			 audit_info->sessionid);

	अगर (audit_info->secid != 0 &&
	    security_secid_to_secctx(audit_info->secid,
				     &secctx,
				     &secctx_len) == 0) अणु
		audit_log_क्रमmat(audit_buf, " subj=%s", secctx);
		security_release_secctx(secctx, secctx_len);
	पूर्ण

	वापस audit_buf;
पूर्ण
