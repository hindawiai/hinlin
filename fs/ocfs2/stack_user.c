<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * stack_user.c
 *
 * Code which पूर्णांकerfaces ocfs2 with fs/dlm and a userspace stack.
 *
 * Copyright (C) 2007 Oracle.  All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>

#समावेश "stackglue.h"

#समावेश <linux/dlm_plock.h>

/*
 * The control protocol starts with a handshake.  Until the handshake
 * is complete, the control device will fail all ग_लिखो(2)s.
 *
 * The handshake is simple.  First, the client पढ़ोs until खातापूर्ण.  Each line
 * of output is a supported protocol tag.  All protocol tags are a single
 * अक्षरacter followed by a two hex digit version number.  Currently the
 * only things supported is T01, क्रम "Text-base version 0x01".  Next, the
 * client ग_लिखोs the version they would like to use, including the newline.
 * Thus, the protocol tag is 'T01\n'.  If the version tag written is
 * unknown, -EINVAL is वापसed.  Once the negotiation is complete, the
 * client can start sending messages.
 *
 * The T01 protocol has three messages.  First is the "SETN" message.
 * It has the following syntax:
 *
 *  SETN<space><8-अक्षर-hex-nodक्रमागत><newline>
 *
 * This is 14 अक्षरacters.
 *
 * The "SETN" message must be the first message following the protocol.
 * It tells ocfs2_control the local node number.
 *
 * Next comes the "SETV" message.  It has the following syntax:
 *
 *  SETV<space><2-अक्षर-hex-major><space><2-अक्षर-hex-minor><newline>
 *
 * This is 11 अक्षरacters.
 *
 * The "SETV" message sets the fileप्रणाली locking protocol version as
 * negotiated by the client.  The client negotiates based on the maximum
 * version advertised in /sys/fs/ocfs2/max_locking_protocol.  The major
 * number from the "SETV" message must match
 * ocfs2_user_plugin.sp_max_proto.pv_major, and the minor number
 * must be less than or equal to ...sp_max_version.pv_minor.
 *
 * Once this inक्रमmation has been set, mounts will be allowed.  From this
 * poपूर्णांक on, the "DOWN" message can be sent क्रम node करोwn notअगरication.
 * It has the following syntax:
 *
 *  DOWN<space><32-अक्षर-cap-hex-uuid><space><8-अक्षर-hex-nodक्रमागत><newline>
 *
 * eg:
 *
 *  DOWN 632A924FDD844190BDA93C0DF6B94899 00000001\न
 *
 * This is 47 अक्षरacters.
 */

/*
 * Whether or not the client has करोne the handshake.
 * For now, we have just one protocol version.
 */
#घोषणा OCFS2_CONTROL_PROTO			"T01\n"
#घोषणा OCFS2_CONTROL_PROTO_LEN			4

/* Handshake states */
#घोषणा OCFS2_CONTROL_HANDSHAKE_INVALID		(0)
#घोषणा OCFS2_CONTROL_HANDSHAKE_READ		(1)
#घोषणा OCFS2_CONTROL_HANDSHAKE_PROTOCOL	(2)
#घोषणा OCFS2_CONTROL_HANDSHAKE_VALID		(3)

/* Messages */
#घोषणा OCFS2_CONTROL_MESSAGE_OP_LEN		4
#घोषणा OCFS2_CONTROL_MESSAGE_SETNODE_OP	"SETN"
#घोषणा OCFS2_CONTROL_MESSAGE_SETNODE_TOTAL_LEN	14
#घोषणा OCFS2_CONTROL_MESSAGE_SETVERSION_OP	"SETV"
#घोषणा OCFS2_CONTROL_MESSAGE_SETVERSION_TOTAL_LEN	11
#घोषणा OCFS2_CONTROL_MESSAGE_DOWN_OP		"DOWN"
#घोषणा OCFS2_CONTROL_MESSAGE_DOWN_TOTAL_LEN	47
#घोषणा OCFS2_TEXT_UUID_LEN			32
#घोषणा OCFS2_CONTROL_MESSAGE_VERNUM_LEN	2
#घोषणा OCFS2_CONTROL_MESSAGE_NODENUM_LEN	8
#घोषणा VERSION_LOCK				"version_lock"

क्रमागत ocfs2_connection_type अणु
	WITH_CONTROLD,
	NO_CONTROLD
पूर्ण;

/*
 * ocfs2_live_connection is refcounted because the fileप्रणाली and
 * miscdevice sides can detach in dअगरferent order.  Let's just be safe.
 */
काष्ठा ocfs2_live_connection अणु
	काष्ठा list_head		oc_list;
	काष्ठा ocfs2_cluster_connection	*oc_conn;
	क्रमागत ocfs2_connection_type	oc_type;
	atomic_t                        oc_this_node;
	पूर्णांक                             oc_our_slot;
	काष्ठा dlm_lksb                 oc_version_lksb;
	अक्षर                            oc_lvb[DLM_LVB_LEN];
	काष्ठा completion               oc_sync_रुको;
	रुको_queue_head_t		oc_रुको;
पूर्ण;

काष्ठा ocfs2_control_निजी अणु
	काष्ठा list_head op_list;
	पूर्णांक op_state;
	पूर्णांक op_this_node;
	काष्ठा ocfs2_protocol_version op_proto;
पूर्ण;

/* SETN<space><8-अक्षर-hex-nodक्रमागत><newline> */
काष्ठा ocfs2_control_message_setn अणु
	अक्षर	tag[OCFS2_CONTROL_MESSAGE_OP_LEN];
	अक्षर	space;
	अक्षर	nodestr[OCFS2_CONTROL_MESSAGE_NODENUM_LEN];
	अक्षर	newline;
पूर्ण;

/* SETV<space><2-अक्षर-hex-major><space><2-अक्षर-hex-minor><newline> */
काष्ठा ocfs2_control_message_setv अणु
	अक्षर	tag[OCFS2_CONTROL_MESSAGE_OP_LEN];
	अक्षर	space1;
	अक्षर	major[OCFS2_CONTROL_MESSAGE_VERNUM_LEN];
	अक्षर	space2;
	अक्षर	minor[OCFS2_CONTROL_MESSAGE_VERNUM_LEN];
	अक्षर	newline;
पूर्ण;

/* DOWN<space><32-अक्षर-cap-hex-uuid><space><8-अक्षर-hex-nodक्रमागत><newline> */
काष्ठा ocfs2_control_message_करोwn अणु
	अक्षर	tag[OCFS2_CONTROL_MESSAGE_OP_LEN];
	अक्षर	space1;
	अक्षर	uuid[OCFS2_TEXT_UUID_LEN];
	अक्षर	space2;
	अक्षर	nodestr[OCFS2_CONTROL_MESSAGE_NODENUM_LEN];
	अक्षर	newline;
पूर्ण;

जोड़ ocfs2_control_message अणु
	अक्षर					tag[OCFS2_CONTROL_MESSAGE_OP_LEN];
	काष्ठा ocfs2_control_message_setn	u_setn;
	काष्ठा ocfs2_control_message_setv	u_setv;
	काष्ठा ocfs2_control_message_करोwn	u_करोwn;
पूर्ण;

अटल काष्ठा ocfs2_stack_plugin ocfs2_user_plugin;

अटल atomic_t ocfs2_control_खोलोed;
अटल पूर्णांक ocfs2_control_this_node = -1;
अटल काष्ठा ocfs2_protocol_version running_proto;

अटल LIST_HEAD(ocfs2_live_connection_list);
अटल LIST_HEAD(ocfs2_control_निजी_list);
अटल DEFINE_MUTEX(ocfs2_control_lock);

अटल अंतरभूत व्योम ocfs2_control_set_handshake_state(काष्ठा file *file,
						     पूर्णांक state)
अणु
	काष्ठा ocfs2_control_निजी *p = file->निजी_data;
	p->op_state = state;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_control_get_handshake_state(काष्ठा file *file)
अणु
	काष्ठा ocfs2_control_निजी *p = file->निजी_data;
	वापस p->op_state;
पूर्ण

अटल काष्ठा ocfs2_live_connection *ocfs2_connection_find(स्थिर अक्षर *name)
अणु
	माप_प्रकार len = म_माप(name);
	काष्ठा ocfs2_live_connection *c;

	BUG_ON(!mutex_is_locked(&ocfs2_control_lock));

	list_क्रम_each_entry(c, &ocfs2_live_connection_list, oc_list) अणु
		अगर ((c->oc_conn->cc_namelen == len) &&
		    !म_भेदन(c->oc_conn->cc_name, name, len))
			वापस c;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * ocfs2_live_connection काष्ठाures are created underneath the ocfs2
 * mount path.  Since the VFS prevents multiple calls to
 * fill_super(), we can't get dupes here.
 */
अटल पूर्णांक ocfs2_live_connection_attach(काष्ठा ocfs2_cluster_connection *conn,
				     काष्ठा ocfs2_live_connection *c)
अणु
	पूर्णांक rc = 0;

	mutex_lock(&ocfs2_control_lock);
	c->oc_conn = conn;

	अगर ((c->oc_type == NO_CONTROLD) || atomic_पढ़ो(&ocfs2_control_खोलोed))
		list_add(&c->oc_list, &ocfs2_live_connection_list);
	अन्यथा अणु
		prपूर्णांकk(KERN_ERR
		       "ocfs2: Userspace control daemon is not present\n");
		rc = -ESRCH;
	पूर्ण

	mutex_unlock(&ocfs2_control_lock);
	वापस rc;
पूर्ण

/*
 * This function disconnects the cluster connection from ocfs2_control.
 * Afterwards, userspace can't affect the cluster connection.
 */
अटल व्योम ocfs2_live_connection_drop(काष्ठा ocfs2_live_connection *c)
अणु
	mutex_lock(&ocfs2_control_lock);
	list_del_init(&c->oc_list);
	c->oc_conn = शून्य;
	mutex_unlock(&ocfs2_control_lock);

	kमुक्त(c);
पूर्ण

अटल पूर्णांक ocfs2_control_cfu(व्योम *target, माप_प्रकार target_len,
			     स्थिर अक्षर __user *buf, माप_प्रकार count)
अणु
	/* The T01 expects ग_लिखो(2) calls to have exactly one command */
	अगर ((count != target_len) ||
	    (count > माप(जोड़ ocfs2_control_message)))
		वापस -EINVAL;

	अगर (copy_from_user(target, buf, target_len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ocfs2_control_validate_protocol(काष्ठा file *file,
					       स्थिर अक्षर __user *buf,
					       माप_प्रकार count)
अणु
	sमाप_प्रकार ret;
	अक्षर kbuf[OCFS2_CONTROL_PROTO_LEN];

	ret = ocfs2_control_cfu(kbuf, OCFS2_CONTROL_PROTO_LEN,
				buf, count);
	अगर (ret)
		वापस ret;

	अगर (म_भेदन(kbuf, OCFS2_CONTROL_PROTO, OCFS2_CONTROL_PROTO_LEN))
		वापस -EINVAL;

	ocfs2_control_set_handshake_state(file,
					  OCFS2_CONTROL_HANDSHAKE_PROTOCOL);

	वापस count;
पूर्ण

अटल व्योम ocfs2_control_send_करोwn(स्थिर अक्षर *uuid,
				    पूर्णांक nodक्रमागत)
अणु
	काष्ठा ocfs2_live_connection *c;

	mutex_lock(&ocfs2_control_lock);

	c = ocfs2_connection_find(uuid);
	अगर (c) अणु
		BUG_ON(c->oc_conn == शून्य);
		c->oc_conn->cc_recovery_handler(nodक्रमागत,
						c->oc_conn->cc_recovery_data);
	पूर्ण

	mutex_unlock(&ocfs2_control_lock);
पूर्ण

/*
 * Called whenever configuration elements are sent to /dev/ocfs2_control.
 * If all configuration elements are present, try to set the global
 * values.  If there is a problem, वापस an error.  Skip any missing
 * elements, and only bump ocfs2_control_खोलोed when we have all elements
 * and are successful.
 */
अटल पूर्णांक ocfs2_control_install_निजी(काष्ठा file *file)
अणु
	पूर्णांक rc = 0;
	पूर्णांक set_p = 1;
	काष्ठा ocfs2_control_निजी *p = file->निजी_data;

	BUG_ON(p->op_state != OCFS2_CONTROL_HANDSHAKE_PROTOCOL);

	mutex_lock(&ocfs2_control_lock);

	अगर (p->op_this_node < 0) अणु
		set_p = 0;
	पूर्ण अन्यथा अगर ((ocfs2_control_this_node >= 0) &&
		   (ocfs2_control_this_node != p->op_this_node)) अणु
		rc = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (!p->op_proto.pv_major) अणु
		set_p = 0;
	पूर्ण अन्यथा अगर (!list_empty(&ocfs2_live_connection_list) &&
		   ((running_proto.pv_major != p->op_proto.pv_major) ||
		    (running_proto.pv_minor != p->op_proto.pv_minor))) अणु
		rc = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (set_p) अणु
		ocfs2_control_this_node = p->op_this_node;
		running_proto.pv_major = p->op_proto.pv_major;
		running_proto.pv_minor = p->op_proto.pv_minor;
	पूर्ण

out_unlock:
	mutex_unlock(&ocfs2_control_lock);

	अगर (!rc && set_p) अणु
		/* We set the global values successfully */
		atomic_inc(&ocfs2_control_खोलोed);
		ocfs2_control_set_handshake_state(file,
					OCFS2_CONTROL_HANDSHAKE_VALID);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक ocfs2_control_get_this_node(व्योम)
अणु
	पूर्णांक rc;

	mutex_lock(&ocfs2_control_lock);
	अगर (ocfs2_control_this_node < 0)
		rc = -EINVAL;
	अन्यथा
		rc = ocfs2_control_this_node;
	mutex_unlock(&ocfs2_control_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक ocfs2_control_करो_setnode_msg(काष्ठा file *file,
					काष्ठा ocfs2_control_message_setn *msg)
अणु
	दीर्घ nodक्रमागत;
	अक्षर *ptr = शून्य;
	काष्ठा ocfs2_control_निजी *p = file->निजी_data;

	अगर (ocfs2_control_get_handshake_state(file) !=
	    OCFS2_CONTROL_HANDSHAKE_PROTOCOL)
		वापस -EINVAL;

	अगर (म_भेदन(msg->tag, OCFS2_CONTROL_MESSAGE_SETNODE_OP,
		    OCFS2_CONTROL_MESSAGE_OP_LEN))
		वापस -EINVAL;

	अगर ((msg->space != ' ') || (msg->newline != '\n'))
		वापस -EINVAL;
	msg->space = msg->newline = '\0';

	nodक्रमागत = simple_म_से_दीर्घ(msg->nodestr, &ptr, 16);
	अगर (!ptr || *ptr)
		वापस -EINVAL;

	अगर ((nodक्रमागत == दीर्घ_न्यून) || (nodक्रमागत == दीर्घ_उच्च) ||
	    (nodक्रमागत > पूर्णांक_उच्च) || (nodक्रमागत < 0))
		वापस -दुस्फल;
	p->op_this_node = nodक्रमागत;

	वापस ocfs2_control_install_निजी(file);
पूर्ण

अटल पूर्णांक ocfs2_control_करो_setversion_msg(काष्ठा file *file,
					   काष्ठा ocfs2_control_message_setv *msg)
अणु
	दीर्घ major, minor;
	अक्षर *ptr = शून्य;
	काष्ठा ocfs2_control_निजी *p = file->निजी_data;
	काष्ठा ocfs2_protocol_version *max =
		&ocfs2_user_plugin.sp_max_proto;

	अगर (ocfs2_control_get_handshake_state(file) !=
	    OCFS2_CONTROL_HANDSHAKE_PROTOCOL)
		वापस -EINVAL;

	अगर (म_भेदन(msg->tag, OCFS2_CONTROL_MESSAGE_SETVERSION_OP,
		    OCFS2_CONTROL_MESSAGE_OP_LEN))
		वापस -EINVAL;

	अगर ((msg->space1 != ' ') || (msg->space2 != ' ') ||
	    (msg->newline != '\n'))
		वापस -EINVAL;
	msg->space1 = msg->space2 = msg->newline = '\0';

	major = simple_म_से_दीर्घ(msg->major, &ptr, 16);
	अगर (!ptr || *ptr)
		वापस -EINVAL;
	minor = simple_म_से_दीर्घ(msg->minor, &ptr, 16);
	अगर (!ptr || *ptr)
		वापस -EINVAL;

	/*
	 * The major must be between 1 and 255, inclusive.  The minor
	 * must be between 0 and 255, inclusive.  The version passed in
	 * must be within the maximum version supported by the fileप्रणाली.
	 */
	अगर ((major == दीर्घ_न्यून) || (major == दीर्घ_उच्च) ||
	    (major > (u8)-1) || (major < 1))
		वापस -दुस्फल;
	अगर ((minor == दीर्घ_न्यून) || (minor == दीर्घ_उच्च) ||
	    (minor > (u8)-1) || (minor < 0))
		वापस -दुस्फल;
	अगर ((major != max->pv_major) ||
	    (minor > max->pv_minor))
		वापस -EINVAL;

	p->op_proto.pv_major = major;
	p->op_proto.pv_minor = minor;

	वापस ocfs2_control_install_निजी(file);
पूर्ण

अटल पूर्णांक ocfs2_control_करो_करोwn_msg(काष्ठा file *file,
				     काष्ठा ocfs2_control_message_करोwn *msg)
अणु
	दीर्घ nodक्रमागत;
	अक्षर *p = शून्य;

	अगर (ocfs2_control_get_handshake_state(file) !=
	    OCFS2_CONTROL_HANDSHAKE_VALID)
		वापस -EINVAL;

	अगर (म_भेदन(msg->tag, OCFS2_CONTROL_MESSAGE_DOWN_OP,
		    OCFS2_CONTROL_MESSAGE_OP_LEN))
		वापस -EINVAL;

	अगर ((msg->space1 != ' ') || (msg->space2 != ' ') ||
	    (msg->newline != '\n'))
		वापस -EINVAL;
	msg->space1 = msg->space2 = msg->newline = '\0';

	nodक्रमागत = simple_म_से_दीर्घ(msg->nodestr, &p, 16);
	अगर (!p || *p)
		वापस -EINVAL;

	अगर ((nodक्रमागत == दीर्घ_न्यून) || (nodक्रमागत == दीर्घ_उच्च) ||
	    (nodक्रमागत > पूर्णांक_उच्च) || (nodक्रमागत < 0))
		वापस -दुस्फल;

	ocfs2_control_send_करोwn(msg->uuid, nodक्रमागत);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ocfs2_control_message(काष्ठा file *file,
				     स्थिर अक्षर __user *buf,
				     माप_प्रकार count)
अणु
	sमाप_प्रकार ret;
	जोड़ ocfs2_control_message msg;

	/* Try to catch padding issues */
	WARN_ON(दुरत्व(काष्ठा ocfs2_control_message_करोwn, uuid) !=
		(माप(msg.u_करोwn.tag) + माप(msg.u_करोwn.space1)));

	स_रखो(&msg, 0, माप(जोड़ ocfs2_control_message));
	ret = ocfs2_control_cfu(&msg, count, buf, count);
	अगर (ret)
		जाओ out;

	अगर ((count == OCFS2_CONTROL_MESSAGE_SETNODE_TOTAL_LEN) &&
	    !म_भेदन(msg.tag, OCFS2_CONTROL_MESSAGE_SETNODE_OP,
		     OCFS2_CONTROL_MESSAGE_OP_LEN))
		ret = ocfs2_control_करो_setnode_msg(file, &msg.u_setn);
	अन्यथा अगर ((count == OCFS2_CONTROL_MESSAGE_SETVERSION_TOTAL_LEN) &&
		 !म_भेदन(msg.tag, OCFS2_CONTROL_MESSAGE_SETVERSION_OP,
			  OCFS2_CONTROL_MESSAGE_OP_LEN))
		ret = ocfs2_control_करो_setversion_msg(file, &msg.u_setv);
	अन्यथा अगर ((count == OCFS2_CONTROL_MESSAGE_DOWN_TOTAL_LEN) &&
		 !म_भेदन(msg.tag, OCFS2_CONTROL_MESSAGE_DOWN_OP,
			  OCFS2_CONTROL_MESSAGE_OP_LEN))
		ret = ocfs2_control_करो_करोwn_msg(file, &msg.u_करोwn);
	अन्यथा
		ret = -EINVAL;

out:
	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार ocfs2_control_ग_लिखो(काष्ठा file *file,
				   स्थिर अक्षर __user *buf,
				   माप_प्रकार count,
				   loff_t *ppos)
अणु
	sमाप_प्रकार ret;

	चयन (ocfs2_control_get_handshake_state(file)) अणु
		हाल OCFS2_CONTROL_HANDSHAKE_INVALID:
			ret = -EINVAL;
			अवरोध;

		हाल OCFS2_CONTROL_HANDSHAKE_READ:
			ret = ocfs2_control_validate_protocol(file, buf,
							      count);
			अवरोध;

		हाल OCFS2_CONTROL_HANDSHAKE_PROTOCOL:
		हाल OCFS2_CONTROL_HANDSHAKE_VALID:
			ret = ocfs2_control_message(file, buf, count);
			अवरोध;

		शेष:
			BUG();
			ret = -EIO;
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This is a naive version.  If we ever have a new protocol, we'll expand
 * it.  Probably using seq_file.
 */
अटल sमाप_प्रकार ocfs2_control_पढ़ो(काष्ठा file *file,
				  अक्षर __user *buf,
				  माप_प्रकार count,
				  loff_t *ppos)
अणु
	sमाप_प्रकार ret;

	ret = simple_पढ़ो_from_buffer(buf, count, ppos,
			OCFS2_CONTROL_PROTO, OCFS2_CONTROL_PROTO_LEN);

	/* Have we पढ़ो the whole protocol list? */
	अगर (ret > 0 && *ppos >= OCFS2_CONTROL_PROTO_LEN)
		ocfs2_control_set_handshake_state(file,
						  OCFS2_CONTROL_HANDSHAKE_READ);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_control_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ocfs2_control_निजी *p = file->निजी_data;

	mutex_lock(&ocfs2_control_lock);

	अगर (ocfs2_control_get_handshake_state(file) !=
	    OCFS2_CONTROL_HANDSHAKE_VALID)
		जाओ out;

	अगर (atomic_dec_and_test(&ocfs2_control_खोलोed)) अणु
		अगर (!list_empty(&ocfs2_live_connection_list)) अणु
			/* XXX: Do bad things! */
			prपूर्णांकk(KERN_ERR
			       "ocfs2: Unexpected release of ocfs2_control!\n"
			       "       Loss of cluster connection requires "
			       "an emergency restart!\n");
			emergency_restart();
		पूर्ण
		/*
		 * Last valid बंद clears the node number and resets
		 * the locking protocol version
		 */
		ocfs2_control_this_node = -1;
		running_proto.pv_major = 0;
		running_proto.pv_minor = 0;
	पूर्ण

out:
	list_del_init(&p->op_list);
	file->निजी_data = शून्य;

	mutex_unlock(&ocfs2_control_lock);

	kमुक्त(p);

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_control_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ocfs2_control_निजी *p;

	p = kzalloc(माप(काष्ठा ocfs2_control_निजी), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;
	p->op_this_node = -1;

	mutex_lock(&ocfs2_control_lock);
	file->निजी_data = p;
	list_add(&p->op_list, &ocfs2_control_निजी_list);
	mutex_unlock(&ocfs2_control_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations ocfs2_control_fops = अणु
	.खोलो    = ocfs2_control_खोलो,
	.release = ocfs2_control_release,
	.पढ़ो    = ocfs2_control_पढ़ो,
	.ग_लिखो   = ocfs2_control_ग_लिखो,
	.owner   = THIS_MODULE,
	.llseek  = शेष_llseek,
पूर्ण;

अटल काष्ठा miscdevice ocfs2_control_device = अणु
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= "ocfs2_control",
	.fops		= &ocfs2_control_fops,
पूर्ण;

अटल पूर्णांक ocfs2_control_init(व्योम)
अणु
	पूर्णांक rc;

	atomic_set(&ocfs2_control_खोलोed, 0);

	rc = misc_रेजिस्टर(&ocfs2_control_device);
	अगर (rc)
		prपूर्णांकk(KERN_ERR
		       "ocfs2: Unable to register ocfs2_control device "
		       "(errno %d)\n",
		       -rc);

	वापस rc;
पूर्ण

अटल व्योम ocfs2_control_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&ocfs2_control_device);
पूर्ण

अटल व्योम fsdlm_lock_ast_wrapper(व्योम *astarg)
अणु
	काष्ठा ocfs2_dlm_lksb *lksb = astarg;
	पूर्णांक status = lksb->lksb_fsdlm.sb_status;

	/*
	 * For now we're punting on the issue of other non-standard errors
	 * where we can't tell अगर the unlock_ast or lock_ast should be called.
	 * The मुख्य "other error" that's possible is EINVAL which means the
	 * function was called with invalid args, which shouldn't be possible
	 * since the caller here is under our control.  Other non-standard
	 * errors probably fall पूर्णांकo the same category, or otherwise are fatal
	 * which means we can't carry on anyway.
	 */

	अगर (status == -DLM_EUNLOCK || status == -DLM_ECANCEL)
		lksb->lksb_conn->cc_proto->lp_unlock_ast(lksb, 0);
	अन्यथा
		lksb->lksb_conn->cc_proto->lp_lock_ast(lksb);
पूर्ण

अटल व्योम fsdlm_blocking_ast_wrapper(व्योम *astarg, पूर्णांक level)
अणु
	काष्ठा ocfs2_dlm_lksb *lksb = astarg;

	lksb->lksb_conn->cc_proto->lp_blocking_ast(lksb, level);
पूर्ण

अटल पूर्णांक user_dlm_lock(काष्ठा ocfs2_cluster_connection *conn,
			 पूर्णांक mode,
			 काष्ठा ocfs2_dlm_lksb *lksb,
			 u32 flags,
			 व्योम *name,
			 अचिन्हित पूर्णांक namelen)
अणु
	पूर्णांक ret;

	अगर (!lksb->lksb_fsdlm.sb_lvbptr)
		lksb->lksb_fsdlm.sb_lvbptr = (अक्षर *)lksb +
					     माप(काष्ठा dlm_lksb);

	ret = dlm_lock(conn->cc_lockspace, mode, &lksb->lksb_fsdlm,
		       flags|DLM_LKF_NODLCKWT, name, namelen, 0,
		       fsdlm_lock_ast_wrapper, lksb,
		       fsdlm_blocking_ast_wrapper);
	वापस ret;
पूर्ण

अटल पूर्णांक user_dlm_unlock(काष्ठा ocfs2_cluster_connection *conn,
			   काष्ठा ocfs2_dlm_lksb *lksb,
			   u32 flags)
अणु
	पूर्णांक ret;

	ret = dlm_unlock(conn->cc_lockspace, lksb->lksb_fsdlm.sb_lkid,
			 flags, &lksb->lksb_fsdlm, lksb);
	वापस ret;
पूर्ण

अटल पूर्णांक user_dlm_lock_status(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
	वापस lksb->lksb_fsdlm.sb_status;
पूर्ण

अटल पूर्णांक user_dlm_lvb_valid(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
	पूर्णांक invalid = lksb->lksb_fsdlm.sb_flags & DLM_SBF_VALNOTVALID;

	वापस !invalid;
पूर्ण

अटल व्योम *user_dlm_lvb(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
	अगर (!lksb->lksb_fsdlm.sb_lvbptr)
		lksb->lksb_fsdlm.sb_lvbptr = (अक्षर *)lksb +
					     माप(काष्ठा dlm_lksb);
	वापस (व्योम *)(lksb->lksb_fsdlm.sb_lvbptr);
पूर्ण

अटल व्योम user_dlm_dump_lksb(काष्ठा ocfs2_dlm_lksb *lksb)
अणु
पूर्ण

अटल पूर्णांक user_plock(काष्ठा ocfs2_cluster_connection *conn,
		      u64 ino,
		      काष्ठा file *file,
		      पूर्णांक cmd,
		      काष्ठा file_lock *fl)
अणु
	/*
	 * This more or less just demuxes the plock request पूर्णांकo any
	 * one of three dlm calls.
	 *
	 * Internally, fs/dlm will pass these to a misc device, which
	 * a userspace daemon will पढ़ो and ग_लिखो to.
	 *
	 * For now, cancel requests (which happen पूर्णांकernally only),
	 * are turned पूर्णांकo unlocks. Most of this function taken from
	 * gfs2_lock.
	 */

	अगर (cmd == F_CANCELLK) अणु
		cmd = F_SETLK;
		fl->fl_type = F_UNLCK;
	पूर्ण

	अगर (IS_GETLK(cmd))
		वापस dlm_posix_get(conn->cc_lockspace, ino, file, fl);
	अन्यथा अगर (fl->fl_type == F_UNLCK)
		वापस dlm_posix_unlock(conn->cc_lockspace, ino, file, fl);
	अन्यथा
		वापस dlm_posix_lock(conn->cc_lockspace, ino, file, cmd, fl);
पूर्ण

/*
 * Compare a requested locking protocol version against the current one.
 *
 * If the major numbers are dअगरferent, they are incompatible.
 * If the current minor is greater than the request, they are incompatible.
 * If the current minor is less than or equal to the request, they are
 * compatible, and the requester should run at the current minor version.
 */
अटल पूर्णांक fs_protocol_compare(काष्ठा ocfs2_protocol_version *existing,
			       काष्ठा ocfs2_protocol_version *request)
अणु
	अगर (existing->pv_major != request->pv_major)
		वापस 1;

	अगर (existing->pv_minor > request->pv_minor)
		वापस 1;

	अगर (existing->pv_minor < request->pv_minor)
		request->pv_minor = existing->pv_minor;

	वापस 0;
पूर्ण

अटल व्योम lvb_to_version(अक्षर *lvb, काष्ठा ocfs2_protocol_version *ver)
अणु
	काष्ठा ocfs2_protocol_version *pv =
		(काष्ठा ocfs2_protocol_version *)lvb;
	/*
	 * ocfs2_protocol_version has two u8 variables, so we करोn't
	 * need any endian conversion.
	 */
	ver->pv_major = pv->pv_major;
	ver->pv_minor = pv->pv_minor;
पूर्ण

अटल व्योम version_to_lvb(काष्ठा ocfs2_protocol_version *ver, अक्षर *lvb)
अणु
	काष्ठा ocfs2_protocol_version *pv =
		(काष्ठा ocfs2_protocol_version *)lvb;
	/*
	 * ocfs2_protocol_version has two u8 variables, so we करोn't
	 * need any endian conversion.
	 */
	pv->pv_major = ver->pv_major;
	pv->pv_minor = ver->pv_minor;
पूर्ण

अटल व्योम sync_रुको_cb(व्योम *arg)
अणु
	काष्ठा ocfs2_cluster_connection *conn = arg;
	काष्ठा ocfs2_live_connection *lc = conn->cc_निजी;
	complete(&lc->oc_sync_रुको);
पूर्ण

अटल पूर्णांक sync_unlock(काष्ठा ocfs2_cluster_connection *conn,
		काष्ठा dlm_lksb *lksb, अक्षर *name)
अणु
	पूर्णांक error;
	काष्ठा ocfs2_live_connection *lc = conn->cc_निजी;

	error = dlm_unlock(conn->cc_lockspace, lksb->sb_lkid, 0, lksb, conn);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "%s lkid %x error %d\n",
				name, lksb->sb_lkid, error);
		वापस error;
	पूर्ण

	रुको_क्रम_completion(&lc->oc_sync_रुको);

	अगर (lksb->sb_status != -DLM_EUNLOCK) अणु
		prपूर्णांकk(KERN_ERR "%s lkid %x status %d\n",
				name, lksb->sb_lkid, lksb->sb_status);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sync_lock(काष्ठा ocfs2_cluster_connection *conn,
		पूर्णांक mode, uपूर्णांक32_t flags,
		काष्ठा dlm_lksb *lksb, अक्षर *name)
अणु
	पूर्णांक error, status;
	काष्ठा ocfs2_live_connection *lc = conn->cc_निजी;

	error = dlm_lock(conn->cc_lockspace, mode, lksb, flags,
			name, म_माप(name),
			0, sync_रुको_cb, conn, शून्य);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR "%s lkid %x flags %x mode %d error %d\n",
				name, lksb->sb_lkid, flags, mode, error);
		वापस error;
	पूर्ण

	रुको_क्रम_completion(&lc->oc_sync_रुको);

	status = lksb->sb_status;

	अगर (status && status != -EAGAIN) अणु
		prपूर्णांकk(KERN_ERR "%s lkid %x flags %x mode %d status %d\n",
				name, lksb->sb_lkid, flags, mode, status);
	पूर्ण

	वापस status;
पूर्ण


अटल पूर्णांक version_lock(काष्ठा ocfs2_cluster_connection *conn, पूर्णांक mode,
		पूर्णांक flags)
अणु
	काष्ठा ocfs2_live_connection *lc = conn->cc_निजी;
	वापस sync_lock(conn, mode, flags,
			&lc->oc_version_lksb, VERSION_LOCK);
पूर्ण

अटल पूर्णांक version_unlock(काष्ठा ocfs2_cluster_connection *conn)
अणु
	काष्ठा ocfs2_live_connection *lc = conn->cc_निजी;
	वापस sync_unlock(conn, &lc->oc_version_lksb, VERSION_LOCK);
पूर्ण

/* get_protocol_version()
 *
 * To exchange ocfs2 versioning, we use the LVB of the version dlm lock.
 * The algorithm is:
 * 1. Attempt to take the lock in EX mode (non-blocking).
 * 2. If successful (which means it is the first mount), ग_लिखो the
 *    version number and करोwnconvert to PR lock.
 * 3. If unsuccessful (वापसs -EAGAIN), पढ़ो the version from the LVB after
 *    taking the PR lock.
 */

अटल पूर्णांक get_protocol_version(काष्ठा ocfs2_cluster_connection *conn)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_live_connection *lc = conn->cc_निजी;
	काष्ठा ocfs2_protocol_version pv;

	running_proto.pv_major =
		ocfs2_user_plugin.sp_max_proto.pv_major;
	running_proto.pv_minor =
		ocfs2_user_plugin.sp_max_proto.pv_minor;

	lc->oc_version_lksb.sb_lvbptr = lc->oc_lvb;
	ret = version_lock(conn, DLM_LOCK_EX,
			DLM_LKF_VALBLK|DLM_LKF_NOQUEUE);
	अगर (!ret) अणु
		conn->cc_version.pv_major = running_proto.pv_major;
		conn->cc_version.pv_minor = running_proto.pv_minor;
		version_to_lvb(&running_proto, lc->oc_lvb);
		version_lock(conn, DLM_LOCK_PR, DLM_LKF_CONVERT|DLM_LKF_VALBLK);
	पूर्ण अन्यथा अगर (ret == -EAGAIN) अणु
		ret = version_lock(conn, DLM_LOCK_PR, DLM_LKF_VALBLK);
		अगर (ret)
			जाओ out;
		lvb_to_version(lc->oc_lvb, &pv);

		अगर ((pv.pv_major != running_proto.pv_major) ||
				(pv.pv_minor > running_proto.pv_minor)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		conn->cc_version.pv_major = pv.pv_major;
		conn->cc_version.pv_minor = pv.pv_minor;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल व्योम user_recover_prep(व्योम *arg)
अणु
पूर्ण

अटल व्योम user_recover_slot(व्योम *arg, काष्ठा dlm_slot *slot)
अणु
	काष्ठा ocfs2_cluster_connection *conn = arg;
	prपूर्णांकk(KERN_INFO "ocfs2: Node %d/%d down. Initiating recovery.\n",
			slot->nodeid, slot->slot);
	conn->cc_recovery_handler(slot->nodeid, conn->cc_recovery_data);

पूर्ण

अटल व्योम user_recover_करोne(व्योम *arg, काष्ठा dlm_slot *slots,
		पूर्णांक num_slots, पूर्णांक our_slot,
		uपूर्णांक32_t generation)
अणु
	काष्ठा ocfs2_cluster_connection *conn = arg;
	काष्ठा ocfs2_live_connection *lc = conn->cc_निजी;
	पूर्णांक i;

	क्रम (i = 0; i < num_slots; i++)
		अगर (slots[i].slot == our_slot) अणु
			atomic_set(&lc->oc_this_node, slots[i].nodeid);
			अवरोध;
		पूर्ण

	lc->oc_our_slot = our_slot;
	wake_up(&lc->oc_रुको);
पूर्ण

अटल स्थिर काष्ठा dlm_lockspace_ops ocfs2_ls_ops = अणु
	.recover_prep = user_recover_prep,
	.recover_slot = user_recover_slot,
	.recover_करोne = user_recover_करोne,
पूर्ण;

अटल पूर्णांक user_cluster_disconnect(काष्ठा ocfs2_cluster_connection *conn)
अणु
	version_unlock(conn);
	dlm_release_lockspace(conn->cc_lockspace, 2);
	conn->cc_lockspace = शून्य;
	ocfs2_live_connection_drop(conn->cc_निजी);
	conn->cc_निजी = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक user_cluster_connect(काष्ठा ocfs2_cluster_connection *conn)
अणु
	dlm_lockspace_t *fsdlm;
	काष्ठा ocfs2_live_connection *lc;
	पूर्णांक rc, ops_rv;

	BUG_ON(conn == शून्य);

	lc = kzalloc(माप(काष्ठा ocfs2_live_connection), GFP_KERNEL);
	अगर (!lc)
		वापस -ENOMEM;

	init_रुकोqueue_head(&lc->oc_रुको);
	init_completion(&lc->oc_sync_रुको);
	atomic_set(&lc->oc_this_node, 0);
	conn->cc_निजी = lc;
	lc->oc_type = NO_CONTROLD;

	rc = dlm_new_lockspace(conn->cc_name, conn->cc_cluster_name,
			       DLM_LSFL_FS | DLM_LSFL_NEWEXCL, DLM_LVB_LEN,
			       &ocfs2_ls_ops, conn, &ops_rv, &fsdlm);
	अगर (rc) अणु
		अगर (rc == -EEXIST || rc == -EPROTO)
			prपूर्णांकk(KERN_ERR "ocfs2: Unable to create the "
				"lockspace %s (%d), because a ocfs2-tools "
				"program is running on this file system "
				"with the same name lockspace\n",
				conn->cc_name, rc);
		जाओ out;
	पूर्ण

	अगर (ops_rv == -EOPNOTSUPP) अणु
		lc->oc_type = WITH_CONTROLD;
		prपूर्णांकk(KERN_NOTICE "ocfs2: You seem to be using an older "
				"version of dlm_controld and/or ocfs2-tools."
				" Please consider upgrading.\n");
	पूर्ण अन्यथा अगर (ops_rv) अणु
		rc = ops_rv;
		जाओ out;
	पूर्ण
	conn->cc_lockspace = fsdlm;

	rc = ocfs2_live_connection_attach(conn, lc);
	अगर (rc)
		जाओ out;

	अगर (lc->oc_type == NO_CONTROLD) अणु
		rc = get_protocol_version(conn);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "ocfs2: Could not determine"
					" locking version\n");
			user_cluster_disconnect(conn);
			जाओ out;
		पूर्ण
		रुको_event(lc->oc_रुको, (atomic_पढ़ो(&lc->oc_this_node) > 0));
	पूर्ण

	/*
	 * running_proto must have been set beक्रमe we allowed any mounts
	 * to proceed.
	 */
	अगर (fs_protocol_compare(&running_proto, &conn->cc_version)) अणु
		prपूर्णांकk(KERN_ERR
		       "Unable to mount with fs locking protocol version "
		       "%u.%u because negotiated protocol is %u.%u\n",
		       conn->cc_version.pv_major, conn->cc_version.pv_minor,
		       running_proto.pv_major, running_proto.pv_minor);
		rc = -EPROTO;
		ocfs2_live_connection_drop(lc);
		lc = शून्य;
	पूर्ण

out:
	अगर (rc)
		kमुक्त(lc);
	वापस rc;
पूर्ण


अटल पूर्णांक user_cluster_this_node(काष्ठा ocfs2_cluster_connection *conn,
				  अचिन्हित पूर्णांक *this_node)
अणु
	पूर्णांक rc;
	काष्ठा ocfs2_live_connection *lc = conn->cc_निजी;

	अगर (lc->oc_type == WITH_CONTROLD)
		rc = ocfs2_control_get_this_node();
	अन्यथा अगर (lc->oc_type == NO_CONTROLD)
		rc = atomic_पढ़ो(&lc->oc_this_node);
	अन्यथा
		rc = -EINVAL;

	अगर (rc < 0)
		वापस rc;

	*this_node = rc;
	वापस 0;
पूर्ण

अटल काष्ठा ocfs2_stack_operations ocfs2_user_plugin_ops = अणु
	.connect	= user_cluster_connect,
	.disconnect	= user_cluster_disconnect,
	.this_node	= user_cluster_this_node,
	.dlm_lock	= user_dlm_lock,
	.dlm_unlock	= user_dlm_unlock,
	.lock_status	= user_dlm_lock_status,
	.lvb_valid	= user_dlm_lvb_valid,
	.lock_lvb	= user_dlm_lvb,
	.plock		= user_plock,
	.dump_lksb	= user_dlm_dump_lksb,
पूर्ण;

अटल काष्ठा ocfs2_stack_plugin ocfs2_user_plugin = अणु
	.sp_name	= "user",
	.sp_ops		= &ocfs2_user_plugin_ops,
	.sp_owner	= THIS_MODULE,
पूर्ण;


अटल पूर्णांक __init ocfs2_user_plugin_init(व्योम)
अणु
	पूर्णांक rc;

	rc = ocfs2_control_init();
	अगर (!rc) अणु
		rc = ocfs2_stack_glue_रेजिस्टर(&ocfs2_user_plugin);
		अगर (rc)
			ocfs2_control_निकास();
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम __निकास ocfs2_user_plugin_निकास(व्योम)
अणु
	ocfs2_stack_glue_unरेजिस्टर(&ocfs2_user_plugin);
	ocfs2_control_निकास();
पूर्ण

MODULE_AUTHOR("Oracle");
MODULE_DESCRIPTION("ocfs2 driver for userspace cluster stacks");
MODULE_LICENSE("GPL");
module_init(ocfs2_user_plugin_init);
module_निकास(ocfs2_user_plugin_निकास);
