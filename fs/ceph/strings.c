<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ceph fs string स्थिरants
 */
#समावेश <linux/module.h>
#समावेश <linux/ceph/types.h>


स्थिर अक्षर *ceph_mds_state_name(पूर्णांक s)
अणु
	चयन (s) अणु
		/* करोwn and out */
	हाल CEPH_MDS_STATE_DNE:        वापस "down:dne";
	हाल CEPH_MDS_STATE_STOPPED:    वापस "down:stopped";
		/* up and out */
	हाल CEPH_MDS_STATE_BOOT:       वापस "up:boot";
	हाल CEPH_MDS_STATE_STANDBY:    वापस "up:standby";
	हाल CEPH_MDS_STATE_STANDBY_REPLAY:    वापस "up:standby-replay";
	हाल CEPH_MDS_STATE_REPLAYONCE: वापस "up:oneshot-replay";
	हाल CEPH_MDS_STATE_CREATING:   वापस "up:creating";
	हाल CEPH_MDS_STATE_STARTING:   वापस "up:starting";
		/* up and in */
	हाल CEPH_MDS_STATE_REPLAY:     वापस "up:replay";
	हाल CEPH_MDS_STATE_RESOLVE:    वापस "up:resolve";
	हाल CEPH_MDS_STATE_RECONNECT:  वापस "up:reconnect";
	हाल CEPH_MDS_STATE_REJOIN:     वापस "up:rejoin";
	हाल CEPH_MDS_STATE_CLIENTREPLAY: वापस "up:clientreplay";
	हाल CEPH_MDS_STATE_ACTIVE:     वापस "up:active";
	हाल CEPH_MDS_STATE_STOPPING:   वापस "up:stopping";
	पूर्ण
	वापस "???";
पूर्ण

स्थिर अक्षर *ceph_session_op_name(पूर्णांक op)
अणु
	चयन (op) अणु
	हाल CEPH_SESSION_REQUEST_OPEN: वापस "request_open";
	हाल CEPH_SESSION_OPEN: वापस "open";
	हाल CEPH_SESSION_REQUEST_CLOSE: वापस "request_close";
	हाल CEPH_SESSION_CLOSE: वापस "close";
	हाल CEPH_SESSION_REQUEST_RENEWCAPS: वापस "request_renewcaps";
	हाल CEPH_SESSION_RENEWCAPS: वापस "renewcaps";
	हाल CEPH_SESSION_STALE: वापस "stale";
	हाल CEPH_SESSION_RECALL_STATE: वापस "recall_state";
	हाल CEPH_SESSION_FLUSHMSG: वापस "flushmsg";
	हाल CEPH_SESSION_FLUSHMSG_ACK: वापस "flushmsg_ack";
	हाल CEPH_SESSION_FORCE_RO: वापस "force_ro";
	हाल CEPH_SESSION_REJECT: वापस "reject";
	पूर्ण
	वापस "???";
पूर्ण

स्थिर अक्षर *ceph_mds_op_name(पूर्णांक op)
अणु
	चयन (op) अणु
	हाल CEPH_MDS_OP_LOOKUP:  वापस "lookup";
	हाल CEPH_MDS_OP_LOOKUPHASH:  वापस "lookuphash";
	हाल CEPH_MDS_OP_LOOKUPPARENT:  वापस "lookupparent";
	हाल CEPH_MDS_OP_LOOKUPINO:  वापस "lookupino";
	हाल CEPH_MDS_OP_LOOKUPNAME:  वापस "lookupname";
	हाल CEPH_MDS_OP_GETATTR:  वापस "getattr";
	हाल CEPH_MDS_OP_SETXATTR: वापस "setxattr";
	हाल CEPH_MDS_OP_SETATTR: वापस "setattr";
	हाल CEPH_MDS_OP_RMXATTR: वापस "rmxattr";
	हाल CEPH_MDS_OP_SETLAYOUT: वापस "setlayou";
	हाल CEPH_MDS_OP_SETसूचीLAYOUT: वापस "setdirlayout";
	हाल CEPH_MDS_OP_READसूची: वापस "readdir";
	हाल CEPH_MDS_OP_MKNOD: वापस "mknod";
	हाल CEPH_MDS_OP_LINK: वापस "link";
	हाल CEPH_MDS_OP_UNLINK: वापस "unlink";
	हाल CEPH_MDS_OP_RENAME: वापस "rename";
	हाल CEPH_MDS_OP_MKसूची: वापस "mkdir";
	हाल CEPH_MDS_OP_RMसूची: वापस "rmdir";
	हाल CEPH_MDS_OP_SYMLINK: वापस "symlink";
	हाल CEPH_MDS_OP_CREATE: वापस "create";
	हाल CEPH_MDS_OP_OPEN: वापस "open";
	हाल CEPH_MDS_OP_LOOKUPSNAP: वापस "lookupsnap";
	हाल CEPH_MDS_OP_LSSNAP: वापस "lssnap";
	हाल CEPH_MDS_OP_MKSNAP: वापस "mksnap";
	हाल CEPH_MDS_OP_RMSNAP: वापस "rmsnap";
	हाल CEPH_MDS_OP_RENAMESNAP: वापस "renamesnap";
	हाल CEPH_MDS_OP_SETखाताLOCK: वापस "setfilelock";
	हाल CEPH_MDS_OP_GETखाताLOCK: वापस "getfilelock";
	पूर्ण
	वापस "???";
पूर्ण

स्थिर अक्षर *ceph_cap_op_name(पूर्णांक op)
अणु
	चयन (op) अणु
	हाल CEPH_CAP_OP_GRANT: वापस "grant";
	हाल CEPH_CAP_OP_REVOKE: वापस "revoke";
	हाल CEPH_CAP_OP_TRUNC: वापस "trunc";
	हाल CEPH_CAP_OP_EXPORT: वापस "export";
	हाल CEPH_CAP_OP_IMPORT: वापस "import";
	हाल CEPH_CAP_OP_UPDATE: वापस "update";
	हाल CEPH_CAP_OP_DROP: वापस "drop";
	हाल CEPH_CAP_OP_FLUSH: वापस "flush";
	हाल CEPH_CAP_OP_FLUSH_ACK: वापस "flush_ack";
	हाल CEPH_CAP_OP_FLUSHSNAP: वापस "flushsnap";
	हाल CEPH_CAP_OP_FLUSHSNAP_ACK: वापस "flushsnap_ack";
	हाल CEPH_CAP_OP_RELEASE: वापस "release";
	हाल CEPH_CAP_OP_RENEW: वापस "renew";
	पूर्ण
	वापस "???";
पूर्ण

स्थिर अक्षर *ceph_lease_op_name(पूर्णांक o)
अणु
	चयन (o) अणु
	हाल CEPH_MDS_LEASE_REVOKE: वापस "revoke";
	हाल CEPH_MDS_LEASE_RELEASE: वापस "release";
	हाल CEPH_MDS_LEASE_RENEW: वापस "renew";
	हाल CEPH_MDS_LEASE_REVOKE_ACK: वापस "revoke_ack";
	पूर्ण
	वापस "???";
पूर्ण

स्थिर अक्षर *ceph_snap_op_name(पूर्णांक o)
अणु
	चयन (o) अणु
	हाल CEPH_SNAP_OP_UPDATE: वापस "update";
	हाल CEPH_SNAP_OP_CREATE: वापस "create";
	हाल CEPH_SNAP_OP_DESTROY: वापस "destroy";
	हाल CEPH_SNAP_OP_SPLIT: वापस "split";
	पूर्ण
	वापस "???";
पूर्ण
