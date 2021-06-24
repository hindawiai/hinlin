<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ceph string स्थिरants
 */
#समावेश <linux/module.h>
#समावेश <linux/ceph/types.h>

स्थिर अक्षर *ceph_entity_type_name(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल CEPH_ENTITY_TYPE_MDS: वापस "mds";
	हाल CEPH_ENTITY_TYPE_OSD: वापस "osd";
	हाल CEPH_ENTITY_TYPE_MON: वापस "mon";
	हाल CEPH_ENTITY_TYPE_CLIENT: वापस "client";
	हाल CEPH_ENTITY_TYPE_AUTH: वापस "auth";
	शेष: वापस "unknown";
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ceph_entity_type_name);

स्थिर अक्षर *ceph_auth_proto_name(पूर्णांक proto)
अणु
	चयन (proto) अणु
	हाल CEPH_AUTH_UNKNOWN:
		वापस "unknown";
	हाल CEPH_AUTH_NONE:
		वापस "none";
	हाल CEPH_AUTH_CEPHX:
		वापस "cephx";
	शेष:
		वापस "???";
	पूर्ण
पूर्ण

स्थिर अक्षर *ceph_con_mode_name(पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल CEPH_CON_MODE_UNKNOWN:
		वापस "unknown";
	हाल CEPH_CON_MODE_CRC:
		वापस "crc";
	हाल CEPH_CON_MODE_SECURE:
		वापस "secure";
	शेष:
		वापस "???";
	पूर्ण
पूर्ण

स्थिर अक्षर *ceph_osd_op_name(पूर्णांक op)
अणु
	चयन (op) अणु
#घोषणा GENERATE_CASE(op, opcode, str)	हाल CEPH_OSD_OP_##op: वापस (str);
__CEPH_FORALL_OSD_OPS(GENERATE_CASE)
#अघोषित GENERATE_CASE
	शेष:
		वापस "???";
	पूर्ण
पूर्ण

स्थिर अक्षर *ceph_osd_watch_op_name(पूर्णांक o)
अणु
	चयन (o) अणु
	हाल CEPH_OSD_WATCH_OP_UNWATCH:
		वापस "unwatch";
	हाल CEPH_OSD_WATCH_OP_WATCH:
		वापस "watch";
	हाल CEPH_OSD_WATCH_OP_RECONNECT:
		वापस "reconnect";
	हाल CEPH_OSD_WATCH_OP_PING:
		वापस "ping";
	शेष:
		वापस "???";
	पूर्ण
पूर्ण

स्थिर अक्षर *ceph_osd_state_name(पूर्णांक s)
अणु
	चयन (s) अणु
	हाल CEPH_OSD_EXISTS:
		वापस "exists";
	हाल CEPH_OSD_UP:
		वापस "up";
	हाल CEPH_OSD_AUTOOUT:
		वापस "autoout";
	हाल CEPH_OSD_NEW:
		वापस "new";
	शेष:
		वापस "???";
	पूर्ण
पूर्ण
