<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_CEPH_CLS_LOCK_CLIENT_H
#घोषणा _LINUX_CEPH_CLS_LOCK_CLIENT_H

#समावेश <linux/ceph/osd_client.h>

क्रमागत ceph_cls_lock_type अणु
	CEPH_CLS_LOCK_NONE = 0,
	CEPH_CLS_LOCK_EXCLUSIVE = 1,
	CEPH_CLS_LOCK_SHARED = 2,
पूर्ण;

काष्ठा ceph_locker_id अणु
	काष्ठा ceph_entity_name name;	/* locker's client name */
	अक्षर *cookie;			/* locker's cookie */
पूर्ण;

काष्ठा ceph_locker_info अणु
	काष्ठा ceph_entity_addr addr;	/* locker's address */
पूर्ण;

काष्ठा ceph_locker अणु
	काष्ठा ceph_locker_id id;
	काष्ठा ceph_locker_info info;
पूर्ण;

पूर्णांक ceph_cls_lock(काष्ठा ceph_osd_client *osdc,
		  काष्ठा ceph_object_id *oid,
		  काष्ठा ceph_object_locator *oloc,
		  अक्षर *lock_name, u8 type, अक्षर *cookie,
		  अक्षर *tag, अक्षर *desc, u8 flags);
पूर्णांक ceph_cls_unlock(काष्ठा ceph_osd_client *osdc,
		    काष्ठा ceph_object_id *oid,
		    काष्ठा ceph_object_locator *oloc,
		    अक्षर *lock_name, अक्षर *cookie);
पूर्णांक ceph_cls_अवरोध_lock(काष्ठा ceph_osd_client *osdc,
			काष्ठा ceph_object_id *oid,
			काष्ठा ceph_object_locator *oloc,
			अक्षर *lock_name, अक्षर *cookie,
			काष्ठा ceph_entity_name *locker);
पूर्णांक ceph_cls_set_cookie(काष्ठा ceph_osd_client *osdc,
			काष्ठा ceph_object_id *oid,
			काष्ठा ceph_object_locator *oloc,
			अक्षर *lock_name, u8 type, अक्षर *old_cookie,
			अक्षर *tag, अक्षर *new_cookie);

व्योम ceph_मुक्त_lockers(काष्ठा ceph_locker *lockers, u32 num_lockers);

पूर्णांक ceph_cls_lock_info(काष्ठा ceph_osd_client *osdc,
		       काष्ठा ceph_object_id *oid,
		       काष्ठा ceph_object_locator *oloc,
		       अक्षर *lock_name, u8 *type, अक्षर **tag,
		       काष्ठा ceph_locker **lockers, u32 *num_lockers);

पूर्णांक ceph_cls_निश्चित_locked(काष्ठा ceph_osd_request *req, पूर्णांक which,
			   अक्षर *lock_name, u8 type, अक्षर *cookie, अक्षर *tag);

#पूर्ण_अगर
